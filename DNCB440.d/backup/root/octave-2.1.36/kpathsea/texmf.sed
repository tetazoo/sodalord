s%@prefix@%/usr/local%g
s%@exec_prefix@%/usr/local%g
s%@bindir@%/usr/local/bin%g
s%@scriptdir@%/usr/local/bin%g
s%@libdir@%/usr/local/lib%g
s%@datadir@%/usr/local/share%g
s%@infodir@%/usr/local/info%g
s%@includedir@%/usr/local/include%g
s%@manext@%1%g
s%@mandir@%/usr/local/man/man1%g
s%@texmf@%%g
s%@web2cdir@%/web2c%g
s%@vartexfonts@%/var/tmp/texfonts%g
s%@texinputdir@%/tex%g
s%@mfinputdir@%/metafont%g
s%@mpinputdir@%/metapost%g
s%@fontdir@%/fonts%g
s%@fmtdir@%/web2c%g
s%@basedir@%/web2c%g
s%@memdir@%/web2c%g
s%@texpooldir@%/web2c%g
s%@mfpooldir@%/web2c%g
s%@mppooldir@%/web2c%g
s%@dvips_plain_macrodir@%/tex/plain/dvips%g
s%@dvilj_latex2e_macrodir@%/tex/latex/dvilj%g
s%@dvipsdir@%/dvips%g
s%@psheaderdir@%/dvips%g
s%@default_texsizes@%300:600%g
s%%\$TEXMF%g
/^ *TEXMFMAIN[ =]/s%\$TEXMF%%
/^[% ]*TEXMFLOCAL[ =]/s%\$TEXMF%%
/^ *TEXMFCNF[ =]/s%@web2c@%/web2c%
