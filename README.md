# viruses

Malware archive for security research and writeups. All entries are indexed into `code.db` and browsable at [krisyotam.com/code](https://krisyotam.com/code).

Includes curated sources from [vxunderground/MalwareSourceCode](https://github.com/vxunderground/MalwareSourceCode) and [RamadhanAmizudin/malware](https://github.com/RamadhanAmizudin/malware), reorganized into a unified taxonomy.

## Structure

```
android/        mobile malware (RATs, stealers, banking trojans)
asm/            ~1,100 ancient DOS/Win9x ASM virus source codes (alpha-organized + legacy-win*)
botnet/         botnet frameworks and C2 infrastructure (Mirai, Grum, etc.)
engine/         polymorphic and mutation engines (Win32, BAT, Linux, VBS)
exploit/        CVE-specific exploits, proof-of-concepts, and exploit kits
infector/       file infectors and PE/ELF parasites
linux/          Linux-specific malware (backdoors, rootkits, trojans, Mirai family)
macos/          macOS malware
phishing/       phishing kits and templates
prank/          harmless educational denial-of-service scripts
ransomware/     ransomware source code and leaked builders
research/       malware research, techniques, and libraries
rootkit/        kernel and userland rootkits
trojan/         trojans, RATs, stealers, keyloggers, and malware families
webshell/       PHP webshells, C2 panels, and web-based backdoors
worm/           self-replicating worms
```

## Archive Header Standard

Every source file carries a standard comment header. Format varies by language but fields are consistent:

**C / C++ / Java**
```c
/*
  name      <name>
  type      <category>
  cve       <CVE or —>
  year      <year>
  os        <target os>
  authors   <original authors>
  source    <where this was obtained>
  archived  krisyotam
  notes     <one-line context>
 */
```

**Python**
```python
# ------------------------------------------------------------
# name      <name>
# type      <category>
# ...
# archived  krisyotam
# ------------------------------------------------------------
```

**Shell / Batch / VBS** follow the same pattern using their respective comment syntax (`#`, `::`, `'`).

**HTML**
```html
<!--
     name      <name>
     ...
     archived  krisyotam
-->
```

## Disclaimer

For educational and research purposes only.
