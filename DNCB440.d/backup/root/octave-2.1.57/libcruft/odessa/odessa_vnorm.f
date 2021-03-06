      DOUBLE PRECISION FUNCTION ODESSA_VNORM (N, V, W)
C-----------------------------------------------------------------------
C THIS FUNCTION ROUTINE COMPUTES THE WEIGHTED ROOT-MEAN-SQUARE NORM
C OF THE VECTOR OF LENGTH N CONTAINED IN THE ARRAY V, WITH WEIGHTS
C CONTAINED IN THE ARRAY W OF LENGTH N..
C  ODESSA_VNORM = SQRT( (1/N) * SUM( V(I)*W(I) )**2 )
C PROTECTION FOR UNDERFLOW/OVERFLOW IS ACCOMPLISHED USING TWO
C CONSTANTS WHICH ARE HOPEFULLY APPLICABLE FOR ALL MACHINES.
C THESE ARE:
C     CUTLO = maximum of SQRT(U/EPS)  over all known machines
C     CUTHI = minimum of SQRT(Z)      over all known machines
C WHERE
C     EPS = smallest number s.t. EPS + 1 .GT. 1
C     U   = smallest positive number (underflow limit)
C     Z   = largest number (overflow limit)
C
C DETAILS OF THE ALGORITHM AND OF VALUES OF CUTLO AND CUTHI ARE
C FOUND IN THE BLAS ROUTINE SNRM2 (SEE ALSO ALGORITHM 539, TRANS.
C MATH. SOFTWARE, VOL. 5 NO. 3, 1979, 308-323.
C FOR SINGLE PRECISION, THE FOLLOWING VALUES SHOULD BE UNIVERSAL:
C     DATA CUTLO,CUTHI /4.441E-16,1.304E19/
C FOR DOUBLE PRECISION, USE
C     DATA CUTLO,CUTHI /8.232D-11,1.304D19/
C
C-----------------------------------------------------------------------
      IMPLICIT DOUBLE PRECISION (A-H,O-Z)
      INTEGER NEXT,I,J,N
      DIMENSION V(N),W(N)
      DATA CUTLO,CUTHI /8.232D-11,1.304D19/
      DATA ZERO,ONE/0.0D0,1.0D0/
C  BLAS ALGORITHM
      NEXT = 1
      SUM = ZERO
      I = 1
20    SX = V(I)*W(I)
      GO TO (30,40,70,80),NEXT
30    IF (DABS(SX).GT.CUTLO) GO TO 110
      NEXT = 2
      XMAX = ZERO
40    IF (SX.EQ.ZERO) GO TO 130
      IF (DABS(SX).GT.CUTLO) GO TO 110
      NEXT = 3
      GO TO 60
50    I=J
      NEXT = 4
      SUM = (SUM/SX)/SX
60    XMAX = DABS(SX)
      GO TO 90
70    IF(DABS(SX).GT.CUTLO) GO TO 100
80    IF(DABS(SX).LE.XMAX) GO TO 90
      SUM = ONE + SUM * (XMAX/SX)**2
      XMAX = DABS(SX)
      GO TO 130
90    SUM = SUM + (SX/XMAX)**2
      GO TO 130
100   SUM = (SUM*XMAX)*XMAX
110   HITEST = CUTHI/DBLE(N)
      DO 120 J = I,N
         SX = V(J)*W(J)
         IF(DABS(SX).GE.HITEST) GO TO 50
         SUM = SUM + SX**2
120   CONTINUE
      ODESSA_VNORM = DSQRT(SUM)
      GO TO 140
130   CONTINUE
      I = I + 1
      IF (I.LE.N) GO TO 20
      ODESSA_VNORM = XMAX * DSQRT(SUM)
140   CONTINUE
      RETURN
C----------------------- END OF FUNCTION ODESSA_VNORM -------------------------
      END
