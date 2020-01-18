## Copyright (C) 1996, 1998 Kai P. Mueller
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by the
## Free Software Foundation; either version 2, or (at your option) any
## later version.
##
## Octave is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place, Suite 330, Boston, MA 02111 USA.

## -*- texinfo -*-
## @deftypefn {Function File} {} hinfdemo ()
##
## H_infinity design demos for continuous SISO and MIMO systems and a
## discrete system.  The SISO system is difficult to control because it
## is non minimum phase and unstable.  The second design example
## controls the "jet707" plant, the linearized state space model of a
## Boeing 707-321 aircraft at v=80m/s (M = 0.26, Ga0 = -3 deg, alpha0 =
## 4 deg, kappa = 50 deg).  Inputs: (1) thrust and (2) elevator angle
## outputs: (1) airspeed and (2) pitch angle. The discrete system is a
## stable and second order.
##
## @table @asis
## @item SISO plant
## @display
## @group
##                 s - 2
##      G(s) = --------------
##             (s + 2)(s - 1)
##
##                               +----+
##          -------------------->| W1 |---> v1
##      z   |                    +----+
##      ----|-------------+                   || T   ||     => min.
##          |             |                       vz   infty
##          |    +---+    v   y  +----+
##        u *--->| G |--->O--*-->| W2 |---> v2
##          |    +---+       |   +----+
##          |                |
##          |    +---+       |
##          -----| K |<-------
##               +---+
## @end group
## @end display
## W1 und W2 are the robustness and performance weighting
## functions
##
## @item MIMO plant
## The optimal controller minimizes the H_infinity norm of the
## augmented plant P (mixed-sensitivity problem):
## @display
## @group
##      w
##       1 -----------+
##                    |                   +----+
##                +---------------------->| W1 |----> z1
##      w         |   |                   +----+
##       2 ------------------------+
##                |   |            |
##                |   v   +----+   v      +----+
##             +--*-->o-->| G  |-->o--*-->| W2 |---> z2
##             |          +----+      |   +----+
##             |                      |
##             ^                      v
##              u (from                 y (to K)
##                controller
##                K)
##
##
##                   +    +           +    +
##                   | z  |           | w  |
##                   |  1 |           |  1 |
##                   | z  | = [ P ] * | w  |
##                   |  2 |           |  2 |
##                   | y  |           | u  |
##                   +    +           +    +
## @end group
## @end display
##
## @item DISCRETE SYSTEM
## This is not a true discrete design. The design is carried out
## in continuous time while the effect of sampling is described by
## a bilinear transformation of the sampled system.
## This method works quite well if the sampling period is "small"
## compared to the plant time constants.
##
## @item The continuous plant
## @display
## @group
##                    1
##      G (s) = --------------
##       k      (s + 2)(s + 1)
##
## @end group
## @end display
## is discretised with a ZOH (Sampling period = Ts = 1 second):
## @display
## @group
##
##                0.199788z + 0.073498
##      G(s) = --------------------------
##             (z - 0.36788)(z - 0.13534)
##
##                               +----+
##          -------------------->| W1 |---> v1
##      z   |                    +----+
##      ----|-------------+                   || T   ||     => min.
##          |             |                       vz   infty
##          |    +---+    v      +----+
##          *--->| G |--->O--*-->| W2 |---> v2
##          |    +---+       |   +----+
##          |                |
##          |    +---+       |
##          -----| K |<-------
##               +---+
## @end group
## @end display
## W1 and W2 are the robustness and performancs weighting
## functions
## @end table
## @end deftypefn

## Author: Kai P. Mueller <mueller@ifr.ing.tu-bs.de>
## Created: April 30, 1998

yn = [];
while (length(yn) < 1)
  yn = input(" * [s]iso, [m]imo, or [d]iscrete design? [no default]: ","S");
endwhile
if ((yn(1) == "s") | (yn(1) == 'S'))
  sys_type = 1;
elseif ((yn(1) == "m") | (yn(1) == 'M'))
  sys_type = 2;
elseif ((yn(1) == "d") | (yn(1) == 'D'))
  sys_type = 3;
else
  disp(" *** no system type specified, hinfdemo terminated.");
  return;
endif

echo off
switch (sys_type)

  case (1)
    ## siso
    disp(" ");
    disp("    ----------------------------------------------");
    disp("    H_infinity optimal control for the SISO plant:");
    disp(" ");
    disp("                          s - 2");
    disp("              G(s) = --------------");
    disp("                     (s + 2)(s - 1)");
    disp(" ");
    disp("    ----------------------------------------------");
    disp(" ");

    ## weighting on actuator u
    W1 = wgt1o(0.05, 100.0, 425.0);
    ## weighting on controlled variable y
    W2 = wgt1o(10.0, 0.05, 0.001);
    ## plant
    G = tf2sys([1 -2],[1 1 -2]);

    ## need One as the pseudo transfer function One = 1
    One = ugain(1);
    disp(" o forming P...");
    psys = buildssic([1 4;2 4;3 1],[3],[2 3 5],[3 4],G,W1,W2,One);
    disp(" ");
    disp(" o controller design...");
    [K, gfin, GW]=hinfsyn(psys, 1, 1, 0.1, 10.0, 0.02);
    disp(" ");
    disp("-- OK ----------------------------------------------");

    disp("  Closed loop poles:");
    damp(GW);
    ## disp(" o Testing H_infinity norm: (hinfnorm does not work)");
    ## hinfnorm(GW);

    disp(" ");
    yn = input(" * Plot closed loop step response? [n]: ","S");
    if (length(yn) >= 1)
      if ((yn(1) == "y") || (yn(1) == 'Y'))
        disp(" o step responses of T and KS...");
        GW = buildssic([1 2; 2 1], [], [1 2], [-2], G, K);
        figure(1);
        step(GW, 1, 10);
      endif
    endif

  case (2)
    ## mimo
    disp(" ");
    disp("    -----------------------------------------------");
    disp("      H_inf optimal control for the jet707 plant");
    disp("    -----------------------------------------------");
    disp(" ");

    ## Weighting function on u (robustness weight)
    ww1 = wgt1o(0.01,5,0.9);
    ww2 = wgt1o(0.01,5,2.2);
    W1 = buildssic([1 0;2 0],[],[1 2],[1 2],ww1,ww2);
    ## Weighting function on y (performance weight)
    ww1 = wgt1o(250,0.1,0.0001);
    ww2 = wgt1o(250,0.1,0.0002);
    W2 = buildssic([1 0;2 0],[],[1 2],[1 2],ww1,ww2);
    ## plant (2 x 2 system)
    G = jet707;

    disp(" o forming P...");
    One = ugain(2);
    Clst = [1 7; 2 8; 3 7; 4 8; 5 1; 6 2];
    P = buildssic(Clst,[5 6],[3:6 9 10],[1 2 5:8],G,W1,W2,One);

    disp(" ");
    disp(" o controller design...");
    K = hinfsyn(P, 2, 2, 0.25, 10.0, 0.005);

    disp(" ");
    yn = input(" * Plot closed loop step responses? [n]: ","S");
    if (length(yn) >= 1)
      if ((yn(1) == "y") || (yn(1) == 'Y'))
        disp(" o step responses of T and KS...");
        GW = buildssic([1 3;2 4;3 1;4 2],[],[1 2 3 4],[-3 -4],G,K);

        disp(" ");
        disp("  FIGURE 1: speed refence => 1, pitch angle ref. => 0");
        disp("  ===================================================");
        disp("      y1:  speed                      (should be 1)");
        disp("      y2:  pitch            angle (should remain 0)");
        disp("      y3:  thrust      (should be a slow transient)");
        disp("      y6:  elevator  (should be a faster transient)");
        disp(" ");
        disp("  FIGURE 2: speed refence => 0, pitch angle ref. => 1");
        disp("  ===================================================");
        disp("      y1:  speed                  (should remain 0)");
        disp("      y2:  pitch                angle (should be 1)");
        disp("      y3:  thrust      (should be a slow transient)");
        disp("      y6:  elevator  (should be a faster transient)");
        disp(" ");
        figure(1)
        step(GW);
        figure(2)
        step(GW,2);
      endif
    endif

  case (3)
    ## discrete
    disp(" ");
    disp("    --------------------------------------------------");
    disp("    Discrete H_infinity optimal control for the plant:");
    disp(" ");
    disp("                         0.199788z + 0.073498");
    disp("              G(s) = --------------------------");
    disp("                     (z - 0.36788)(z - 0.13533)");
    disp("    --------------------------------------------------");
    disp(" ");

    ## sampling time
    Ts = 1.0;
    ## weighting on actuator value u
    W1 = wgt1o(0.1, 200.0, 50.0);
    ## weighting on controlled variable y
    W2 = wgt1o(350.0, 0.05, 0.0002);
    ## omega axis
    ww = logspace(-4.99, 3.99, 100);
    if (columns(ww) > 1);  ww = ww';  endif

    ## continuous plant
    G = tf2sys(2,[1 3 2]);
    ## discrete plant with zoh
    Gd = c2d(G, Ts);
    ## w-plane (continuous representation of the sampled system)
    Gw = d2c(Gd, "bi");

    disp(" ");
    disp(" o building P...");
    ## need One as the pseudo transfer function One = 1
    One = ugain(1);
    psys = buildssic([1 4;2 4;3 1],[3],[2 3 5],[3 4],Gw,W1,W2,One);
    disp(" o controller design...");
    [K, gfin, GWC] = hinfsyn(psys, 1, 1, 0.1, 10.0, 0.02);

    disp(" ");
    fig_n = 1;
    yn = input(" * Plot magnitudes of W1KS and W2S? [n]: ","S");
    if (length(yn) >= 1)
      if ((yn(1) == "y") || (yn(1) == 'Y'))
        disp(" o magnitudes of W1KS and W2S...");
        gwx = sysprune(GWC, 1, 1);
        mag1 = bode(gwx, ww);
        if (columns(mag1) > 1);  mag1 = mag1';  endif
        gwx = sysprune(GWC, 2, 1);
        mag2 = bode(gwx, ww);
        if (columns(mag2) > 1);  mag2 = mag2';  endif
        figure(fig_n)
        fig_n = fig_n + 1;
        gset grid
        loglog(ww, [mag1 mag2]);
      endif
    endif

    Kd = c2d(K, "bi", Ts);
    GG = buildssic([1 2; 2 1], [], [1 2], [-2], Gd, Kd);
    disp(" o closed loop poles...");
    damp(GG);

    disp(" ");
    yn = input(" * Plot closed loop step responses? [n]: ","S");
    if (length(yn) >= 1)
      if ((yn(1) == "y") || (yn(1) == 'Y'))
        disp(" o step responses of T and KS...");
        figure(fig_n)
        step(GG, 1, 10);
      endif
    endif

endswitch

disp(" o hinfdemo terminated successfully.");

## KPM-hinfdemo/End
