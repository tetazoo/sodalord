// MIT/Athena default preferences
// This file will be used to generate the user's
// ~/.netscape/preferences.js file. Anywhere
// root is shown, the user's kerberos name
// will be substituted.

// Set our favorite homepage ...
user_pref("browser.startup.homepage", "http://web.mit.edu/");
// ... and prevent the Netcenter page from coming up first time.
user_pref("browser.startup.homepage_override", false);

// Don't offer us those puny license agreements
user_pref("browser.startup.agreed_to_license", true);

//Where the mime types are
user_pref("helpers.global_mailcap_file", "/mit/infoagents/share/Netscape/@sys/mailcap");
user_pref("helpers.global_mime_types_file", "/mit/infoagents/share/Netscape/@sys/mime.types");

// Do not cache to disk by default ...
user_pref("browser.cache.disk_cache_size", 0);
user_pref("browser.cache.memory_cache_size", 4000);
// ... but if they turn it on, try to get them to use /var/tmp
user_pref("browser.cache.directory", "/var/tmp/.netscape-cache-root");

// Email-related settings
user_pref("mail.identity.organization", "Massachusetts Institute of Technology");
user_pref("mail.identity.useremail", "root@mit.edu");
user_pref("mail.identity.defaultdomain", "mit.edu");
user_pref("mail.signature_file", "");
user_pref("mail.use_builtin_movemail", false);
user_pref("mail.movemail_program", "/mit/infoagents/bin/netscape-movemail");
user_pref("mail.server_type", 2);
user_pref("mail.check_new_mail", false);
user_pref("mail.html_compose", false);
user_pref("mail.prompt_purge_threshhold", true);
user_pref("network.hosts.smtp_server", "outgoing.mit.edu");

// News settings
user_pref("network.hosts.nntp_server", "news.mit.edu");

// Accept only cookies from same place as page being viewed
user_pref("network.cookie.cookieBehavior", 1);

// Turn off Smart Browsing/What's Related/Internet Keywords
user_pref("browser.related.enabled", false);
user_pref("browser.goBrowsing.enabled", false);

// Turn off the Shop button
user_pref("browser.chrome.disableMyShopping", true);

// Turn off AutoUpdate
user_pref("autoupdate.enabled", false);

// Java/JScript on. These settings vanish from user's copy
// of file upon 1st run - they are defaults, and
// Netscape only records settings that are non-default.
user_pref("javascript.enabled", true);
user_pref("security.enable_java", true);

// Our local print command
user_pref("print.print_command", "lpr");
