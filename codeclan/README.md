Code Clan
=========
Coding game using commandline, a prototype

In order to add new missions and/or categories to code clan simply add properly into
clanrepo directory.

using fork() and exec() can get tricky. exec() parameters which are a relative directory
structure doesn't seem to work well. Or I was just too incompetent. Ended up switching
directory between fork() and exec().
