      DOUBLE PRECISION FUNCTION ODESSA_ADDX(A,B)
      DOUBLE PRECISION A,B
C
C  THIS FUNCTION IS NECESSARY TO FORCE OPTIMIZING COMPILERS TO
C  EXECUTE AND STORE A SUM, FOR SUCCESSFUL EXECUTION OF THE
C  TEST A + B = B.
C
      ODESSA_ADDX = A + B
      RETURN
C-------------------- END OF FUNCTION SUM ------------------------------
      END