warn_fortran_indexing = 0;
a = [9,8;7,6];
all (a(1,logical ([1,1])) == [9,8])
