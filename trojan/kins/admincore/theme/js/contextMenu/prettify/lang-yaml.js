/*
  name      KINS
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
var a=null;
PR.registerLangHandler(PR.createSimpleLexer([["pun",/^[:>?|]+/,a,":|>?"],["dec",/^%(?:YAML|TAG)[^\n\r#]+/,a,"%"],["typ",/^&\S+/,a,"&"],["typ",/^!\S*/,a,"!"],["str",/^"(?:[^"\\]|\\.)*(?:"|$)/,a,'"'],["str",/^'(?:[^']|'')*(?:'|$)/,a,"'"],["com",/^#[^\n\r]*/,a,"#"],["pln",/^\s+/,a," \t\r\n"]],[["dec",/^(?:---|\.\.\.)(?:[\n\r]|$)/],["pun",/^-/],["kwd",/^\w+:[\n\r ]/],["pln",/^\w+/]]),["yaml","yml"]);
