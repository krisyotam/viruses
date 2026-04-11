#!/usr/bin/env python3
"""
stamp-headers.py — add standardized archive headers to malware source files.

Usage:
    python stamp-headers.py [--dry-run] [--category <name>] [--verbose]
"""

import argparse
import json
import os
import sys

REPO_ROOT = os.path.dirname(os.path.abspath(__file__))
SOURCES_JSON = os.path.join(REPO_ROOT, "SOURCES.json")

STAMPABLE_EXTENSIONS = {
    ".c", ".cpp", ".h", ".java", ".cs", ".go",
    ".py", ".pl", ".rb", ".sh", ".bash",
    ".asm", ".ASM", ".inc",
    ".html", ".htm",
    ".bat", ".cmd",
    ".vbs", ".vba",
    ".php", ".js", ".ts",
}

# Categories and their canonical OS targets
CATEGORY_OS = {
    "asm":       "DOS",
    "android":   "Android",
    "linux":     "Linux",
    "macos":     "macOS",
}
DEFAULT_OS = "Windows"

CATEGORIES = [
    "android", "asm", "botnet", "engine", "exploit", "infector",
    "linux", "macos", "phishing", "prank", "ransomware", "research",
    "rootkit", "trojan", "webshell", "worm",
]


# ---------------------------------------------------------------------------
# Header builders
# ---------------------------------------------------------------------------

def _fields(meta):
    """Return list of (key, value) pairs in canonical order."""
    return [
        ("name",     meta.get("name", "—")),
        ("type",     meta.get("type", "—")),
        ("cve",      meta.get("cve", "—")),
        ("year",     meta.get("year", "—")),
        ("os",       meta.get("os", "—")),
        ("authors",  meta.get("authors", "unknown")),
        ("source",   meta.get("source", "unknown")),
        ("archived", meta.get("archived", "krisyotam (2026)")),
        ("notes",    meta.get("notes", "—")),
    ]


def build_c_header(meta):
    lines = ["/*"]
    for k, v in _fields(meta):
        lines.append(f"  {k:<10}{v}")
    lines.append(" */")
    return "\n".join(lines) + "\n"


def build_hash_header(meta):
    SEP = "# " + "-" * 60
    lines = [SEP]
    for k, v in _fields(meta):
        lines.append(f"# {k:<10}{v}")
    lines.append(SEP)
    return "\n".join(lines) + "\n"


def build_asm_header(meta):
    SEP = "; " + "-" * 60
    lines = [SEP]
    for k, v in _fields(meta):
        lines.append(f"; {k:<10}{v}")
    lines.append(SEP)
    return "\n".join(lines) + "\n"


def build_html_header(meta):
    lines = ["<!--"]
    for k, v in _fields(meta):
        lines.append(f"     {k:<10}{v}")
    lines.append("-->")
    return "\n".join(lines) + "\n"


def build_batch_header(meta):
    SEP = ":: " + "-" * 60
    lines = [SEP]
    for k, v in _fields(meta):
        lines.append(f":: {k:<10}{v}")
    lines.append(SEP)
    return "\n".join(lines) + "\n"


def build_vbs_header(meta):
    SEP = "' " + "-" * 60
    lines = [SEP]
    for k, v in _fields(meta):
        lines.append(f"' {k:<10}{v}")
    lines.append(SEP)
    return "\n".join(lines) + "\n"


def header_for_ext(ext, meta):
    if ext in (".c", ".cpp", ".h", ".java", ".cs", ".go", ".php", ".js", ".ts"):
        return build_c_header(meta)
    elif ext in (".py", ".pl", ".rb", ".sh", ".bash"):
        return build_hash_header(meta)
    elif ext in (".asm", ".ASM", ".inc"):
        return build_asm_header(meta)
    elif ext in (".html", ".htm"):
        return build_html_header(meta)
    elif ext in (".bat", ".cmd"):
        return build_batch_header(meta)
    elif ext in (".vbs", ".vba"):
        return build_vbs_header(meta)
    return None


# ---------------------------------------------------------------------------
# Metadata resolution
# ---------------------------------------------------------------------------

def source_display(raw_source):
    """Map raw source field to display value."""
    if not raw_source or raw_source in ("unknown", ""):
        return "unknown"
    if raw_source == "original":
        return "krisyotam"
    if raw_source == "vxunderground/MalwareSourceCode":
        return "vxunderground"
    return raw_source


def archived_display(archived_by, year="2026"):
    """Format archived_by list into display string."""
    if not archived_by:
        return f"krisyotam ({year})"
    joined = ", ".join(archived_by)
    return f"{joined} ({year})"


def infer_meta_from_path(filepath):
    """Infer metadata fields from the file's path within the repo."""
    rel = os.path.relpath(filepath, REPO_ROOT)
    parts = rel.split(os.sep)

    category = parts[0] if len(parts) >= 1 else "unknown"
    # immediate parent dir gives the sample name
    parent_dir = parts[-2] if len(parts) >= 2 else parts[0]
    name = parent_dir.replace("-", " ").replace("_", " ").title()

    os_target = CATEGORY_OS.get(category, DEFAULT_OS)

    return {
        "name":     name,
        "type":     category,
        "cve":      "—",
        "year":     "—",
        "os":       os_target,
        "authors":  "unknown",
        "source":   "unknown",
        "archived": "krisyotam (2026)",
        "notes":    "—",
    }


def resolve_meta(filepath, sources):
    """Build metadata dict for a file, merging SOURCES.json data over inferred defaults."""
    meta = infer_meta_from_path(filepath)

    rel = os.path.relpath(filepath, REPO_ROOT)
    parts = rel.split(os.sep)

    # Try keys: "category/dirname" and "category/dirname/..."
    # Most specific match wins, so try longest prefix first
    for depth in range(len(parts), 0, -1):
        key = "/".join(parts[:depth])
        if key in sources:
            entry = sources[key]
            if "name" in entry:
                meta["name"] = entry["name"]
            if "type" in entry:
                meta["type"] = entry["type"]
            if "cve" in entry:
                meta["cve"] = entry["cve"]
            if "year" in entry:
                meta["year"] = str(entry["year"])
            if "os" in entry:
                meta["os"] = entry["os"]
            if "authors" in entry:
                a = entry["authors"]
                meta["authors"] = ", ".join(a) if isinstance(a, list) else a
            if "source" in entry:
                meta["source"] = source_display(entry["source"])
            if "archived_by" in entry:
                meta["archived"] = archived_display(
                    entry["archived_by"],
                    "2026"
                )
            if "notes" in entry:
                meta["notes"] = entry["notes"]
            break

    return meta


# ---------------------------------------------------------------------------
# File processing
# ---------------------------------------------------------------------------

def is_binary(path, sample_size=8192):
    """Quick heuristic: if the first sample_size bytes contain a null byte, treat as binary."""
    try:
        with open(path, "rb") as f:
            chunk = f.read(sample_size)
        return b"\x00" in chunk
    except OSError:
        return True


def already_stamped(path):
    """Return True if 'archived' appears within the first 20 lines."""
    try:
        with open(path, "r", errors="replace") as f:
            for i, line in enumerate(f):
                if i >= 20:
                    break
                if "archived" in line:
                    return True
    except OSError:
        return True
    return False


def stamp_file(filepath, meta, dry_run=False, verbose=False):
    """
    Prepend the appropriate header to the file.
    Preserves shebang lines.
    Returns True on success, False on failure.
    """
    ext = os.path.splitext(filepath)[1]
    header = header_for_ext(ext, meta)
    if header is None:
        return False

    try:
        with open(filepath, "r", errors="replace") as f:
            original = f.read()
    except OSError as e:
        if verbose:
            print(f"  ERROR reading {filepath}: {e}")
        return False

    # Handle shebang
    shebang = ""
    body = original
    if original.startswith("#!"):
        nl = original.find("\n")
        if nl != -1:
            shebang = original[: nl + 1]
            body = original[nl + 1 :]
        else:
            shebang = original
            body = ""

    new_content = shebang + header + body

    if verbose:
        print(f"  stamp  {os.path.relpath(filepath, REPO_ROOT)}")

    if not dry_run:
        try:
            with open(filepath, "w", errors="replace") as f:
                f.write(new_content)
        except OSError as e:
            if verbose:
                print(f"  ERROR writing {filepath}: {e}")
            return False

    return True


# ---------------------------------------------------------------------------
# Walk
# ---------------------------------------------------------------------------

def collect_files(category=None):
    """Yield absolute paths for all files under the relevant categories."""
    cats = [category] if category else CATEGORIES
    for cat in cats:
        cat_dir = os.path.join(REPO_ROOT, cat)
        if not os.path.isdir(cat_dir):
            continue
        for dirpath, _dirnames, filenames in os.walk(cat_dir):
            for fname in filenames:
                yield os.path.join(dirpath, fname)


def load_sources():
    if not os.path.isfile(SOURCES_JSON):
        return {}
    try:
        with open(SOURCES_JSON) as f:
            return json.load(f)
    except (json.JSONDecodeError, OSError) as e:
        print(f"Warning: could not load SOURCES.json: {e}", file=sys.stderr)
        return {}


def run(dry_run=False, category=None, verbose=False):
    sources = load_sources()

    stamped = 0
    skipped_header = 0
    skipped_other = 0
    total = 0

    for filepath in collect_files(category):
        total += 1
        ext = os.path.splitext(filepath)[1]

        # Extension filter
        if ext not in STAMPABLE_EXTENSIONS:
            skipped_other += 1
            if verbose:
                print(f"  skip   {os.path.relpath(filepath, REPO_ROOT)}  [unsupported ext]")
            continue

        # Size filter
        try:
            size = os.path.getsize(filepath)
        except OSError:
            skipped_other += 1
            continue
        if size < 10:
            skipped_other += 1
            if verbose:
                print(f"  skip   {os.path.relpath(filepath, REPO_ROOT)}  [too small]")
            continue

        # Binary filter
        if is_binary(filepath):
            skipped_other += 1
            if verbose:
                print(f"  skip   {os.path.relpath(filepath, REPO_ROOT)}  [binary]")
            continue

        # Already stamped
        if already_stamped(filepath):
            skipped_header += 1
            if verbose:
                print(f"  skip   {os.path.relpath(filepath, REPO_ROOT)}  [already stamped]")
            continue

        meta = resolve_meta(filepath, sources)
        ok = stamp_file(filepath, meta, dry_run=dry_run, verbose=verbose)
        if ok:
            stamped += 1
        else:
            skipped_other += 1

    print()
    label = "[DRY RUN] " if dry_run else ""
    print(f"{label}Results:")
    print(f"  stamped          : {stamped}")
    print(f"  skipped (header) : {skipped_header}")
    print(f"  skipped (other)  : {skipped_other}")
    print(f"  total seen       : {total}")


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(
        description="Add standardized archive headers to malware source files."
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print what would be done without modifying files.",
    )
    parser.add_argument(
        "--category",
        metavar="NAME",
        help="Only process one category (e.g. trojan).",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Print each file as it is processed.",
    )
    args = parser.parse_args()

    if args.category and args.category not in CATEGORIES:
        print(f"Unknown category '{args.category}'. Valid: {', '.join(CATEGORIES)}", file=sys.stderr)
        sys.exit(1)

    run(dry_run=args.dry_run, category=args.category, verbose=args.verbose)


if __name__ == "__main__":
    main()
