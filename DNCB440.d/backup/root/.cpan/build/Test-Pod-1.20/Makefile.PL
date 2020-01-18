# $Id: Makefile.PL,v 1.16 2004/04/29 04:39:06 andy Exp $
use ExtUtils::MakeMaker;

WriteMakefile (
    'NAME'           => 'Test::Pod',
    'VERSION_FROM'   => 'Pod.pm',
    'PREREQ_PM'      => {
        'Pod::Simple'           => '2.04',
        'Test::More'            => 0,
        'Test::Builder::Tester' => 0,
        'File::Spec'            => 0,
    },
    clean => { FILES => 'Test-Pod-*' },
);

