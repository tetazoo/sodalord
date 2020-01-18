      SUBROUTINE ODESSA_RSCOM (RSAV, ISAV)
C-----------------------------------------------------------------------
C THIS ROUTINE RESTORES FROM RSAV AND ISAV THE CONTENTS OF COMMON BLOCKS
C ODE001 AND ODE002, WHICH ARE USED INTERNALLY IN THE ODESSSA
C PACKAGE.  THIS PRESUMES THAT RSAV AND ISAV WERE LOADED BY MEANS
C OF SUBROUTINE ODESSA_SVCOM OR THE EQUIVALENT.
C-----------------------------------------------------------------------
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      DIMENSION RSAV(*), ISAV(*)
      COMMON /ODE001/ RODE1(219), IODE1(39)
      COMMON /ODE002/ RODE2(3), IODE2(11)
      DATA LRODE1/219/, LIODE1/39/, LRODE2/3/, LIODE2/11/
C
      DO 10 I = 1,LRODE1
 10     RODE1(I) = RSAV(I)
      DO 20 I = 1,LRODE2
        J = LRODE1 + I
 20     RODE2(I) = RSAV(J)
      DO 30 I = 1,LIODE1
 30     IODE1(I) = ISAV(I)
      DO 40 I = 1,LIODE2
        J = LIODE1 + I
 40     IODE2(I) = ISAV(J)
      RETURN
C----------------------- END OF SUBROUTINE ODESSA_RSCOM -----------------------
      END