XCOMM Check for /usr/X11R6/bin and BINDIR in the path, if not add them.
XCOMM This allows startx to be placed in a place like /usr/local/bin
XCOMM and people may use X without changing their PATH.

XCOMM First our compiled path
bindir=__bindir__

case $PATH in
    *:$bindir | *:$bindir:* | $bindir:*) ;;
    *) PATH=$bindir:$PATH ;;
esac

XCOMM Now the "old" compiled path
oldbindir=/usr/X11R6/bin

if [ -d "$oldbindir" ] ; then
    case $PATH in
        *:$oldbindir | *:$oldbindir:* | $oldbindir:*) ;;
        *) PATH=$PATH:$oldbindir ;;
    esac
fi

XCOMM Now make sure our preferences domain is set
if [ "x$X11_PREFS_DOMAIN" = x ] ; then
    export X11_PREFS_DOMAIN=BUNDLE_ID_PREFIX".X11"
fi

XCOMM Make sure this has run, just in case.
if [ -x __libexecdir__/privileged_startx ] ; then
	__libexecdir__/privileged_startx &
fi
