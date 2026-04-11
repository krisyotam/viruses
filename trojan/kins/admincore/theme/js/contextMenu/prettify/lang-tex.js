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
PR.registerLangHandler(PR.createSimpleLexer([["pln",/^[\t\n\r \xa0]+/,null,"\t\n\r �\xa0"],["com",/^%[^\n\r]*/,null,"%"]],[["kwd",/^\\[@-Za-z]+/],["kwd",/^\\./],["typ",/^[$&]/],["lit",/[+-]?(?:\.\d+|\d+(?:\.\d*)?)(cm|em|ex|in|pc|pt|bp|mm)/i],["pun",/^[()=[\]{}]+/]]),["latex","tex"]);
