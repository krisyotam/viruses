# viruses

Malware archive for security research and writeups. All entries are indexed into `code.db` and browsable at [krisyotam.com/code](https://krisyotam.com/code).

## Structure

```
asm/            ~1,000 ancient DOS/Win9x ASM virus source codes (alpha-organized)
worm/           self-replicating worms
exploit/        CVE-specific exploits and proof-of-concept implementations
ransomware/     ransomware source code and leaked builders
trojan/         trojans and remote access tools
prank/          harmless educational denial-of-service scripts
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
