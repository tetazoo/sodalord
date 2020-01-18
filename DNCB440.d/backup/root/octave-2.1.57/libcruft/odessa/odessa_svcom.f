      SUBROUTINE ODESSA_SVCOM (RSAV, ISAV)
C-----------------------------------------------------------------------
C THIS ROUTINE STORES IN RSAV AND ISAV THE CONTENTS OF COMMON BLOCKS
C ODE001 AND ODE002, WHICH ARE USED INTERNALLY IN THE ODESSA
C PACKAGE.
C RSAV = REAL ARRAY OF LENGTH 222 OR MORE.
C ISAV = INTEGER ARRAY OF LENGTH 52 OR MORE.
C-----------------------------------------------------------------------
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION RSAV(*), ISAV(*)
      COMMON /ODE001/ RODE1(219), IODE1(39)
      COMMON /ODE002/ RODE2(3), IODE2(11)
      DATA LRODE1/219/, LIODE1/39/, LRODE2/3/, LIODE2/11/
C
      DO 10 I = 1,LRODE1
 10     RSAV(I) = RODE1(I)
      DO 20 I = 1,LRODE2
        J = LRODE1 + I
 20     RSAV(J) = RODE2(I)
      DO 30 I = 1,LIODE1
 30     ISAV(I) = IODE1(I)
      DO 40 I = 1,LIODE2
        J = LIODE1 + I
 40     ISAV(J) = IODE2(I)
      RETURN
C----------------------- END OF SUBROUTINE ODESSA_SVCOM -----------------------
      END
