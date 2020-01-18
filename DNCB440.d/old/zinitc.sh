#!/bin/bash

export KRB5CCNAME=/tmp/krb5cc_sodacard KRBTKFILE=/tmp/tkt_sodacard
#/usr/athena/bin/kdestroy
/usr/athena/bin/kinit -k -t /etc/krb5.keytab
