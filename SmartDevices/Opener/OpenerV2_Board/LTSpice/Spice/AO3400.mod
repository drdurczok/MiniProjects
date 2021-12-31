.SUBCKT AO3400 4 1 2
M1  3 1 2 2 NMOS W=998956u  L=1.0u 
M2  2 1 2 4 PMOS W=998956u  L=0.4u
R1  4 3     RTEMP 15E-3
CGS 1 2     225E-12
DBD 2 3     DBD
**************************************************************************
.MODEL  NMOS       NMOS  (LEVEL  = 3               TOX    = 2.5E-8
+ RS     = 2E-4           RD     = 0               NSUB   = 1.6E17  
+ kp     = 3E-5        	  UO     = 600             THETA  = 0
+ VMAX   = 0              XJ     = 4E-7            KAPPA  = 1.1
+ ETA    = 0              TPG    = 1  
+ IS     = 0              LD     = 0                           
+ CGSO   = 0              CGDO   = 0               CGBO   = 0 
+ NFS    = 2E10         DELTA  = 0.1)
*************************************************************************
.MODEL  PMOS       PMOS (LEVEL   = 3               TOX    = 2.5E-8
+NSUB    = 2.0E16           TPG    = -1)   
*************************************************************************
.MODEL DBD D (CJO=690E-12     VJ=0.6    M=0.3
+RS=0.005 FC=0.5 IS=1E-11 TT=1.5E-8 N=1.0 BV=36 IBV=1E-4)
*************************************************************************
.MODEL RTEMP RES (TC1=6.5E-3   TC2=1E-6)
*************************************************************************
.ENDS
