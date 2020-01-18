%define ver 0.90
%define rel 1
%define prefix /usr

Summary: parapin, a parellel port pin control library
Name: parapin
Version: %ver
Release: %rel
Copyright: GPL
Group: Development/Libraries
Source: ftp://ftp.circlemud.org/pub/jelson/parapin/parapin-0.90.tar.gz

%description

parapin makes it easy to write C code under Linux that controls
individual pins on a PC parallel port. This kind of control is very
useful for electronics projects that use the PC's parallel port as a
generic digital I/O interface. Parapin goes to great lengths to
insulate the programmer from the somewhat complex parallel port
programming interface provided by the PC hardware, making it easy to
use the parallel port for digital I/O.  Parapin has two
``personalities'': it can either be used as a user-space C library, or
linked as part of a Linux kernel module. The user and kernel
personalities were both written with efficiency in mind, so that
Parapin can be used in time-sensitive applications.

%prep
%setup

%build
MYCFLAGS="$RPM_OPT_FLAGS"

make

%install

/usr/bin/install -o bin -g bin -m 755 libparapin.a %{prefix}/lib
/usr/bin/install -o bin -g bin -m 444 parapin.h %{prefix}/include

%clean
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-, root, root)

%doc README
%doc doc/parapin.ps
%doc doc/parapin.txt

%{prefix}/lib/libparapin.a
%{prefix}/include/parapin.h
