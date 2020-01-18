#!/bin/bash

export KRB5CCNAME=/tmp/krb5cc_soda KRBTKFILE=/tmp/tkt_soda
#/usr/athena/bin/kdestroy
/usr/athena/bin/kinit -k -t /etc/krb5.keytab
