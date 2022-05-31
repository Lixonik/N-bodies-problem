      program eps
      implicit none
      real*8 e,u,t
      integer*4 k
      u=1.d0
      k=0
      e=u
 10      t=u+e
         if (t.gt.u) then
                          e=e/2
                          k=k-1
                          go to 10
                       endif
      e=e*2
      k=k+1
      write(6,600) e,k
c
      k=0
      e=1.d0
 20      if (e.gt.0.d0) then
                           e=e/2
                           k=k-1
                           go to 20
                        endif
      k=k+1
      e=2.d0**(k)
      write(6,610) e,k
      stop
 600  format('epsilon de maquina:',e24.16,'      2^(',i3,')')
 610  format('nombre mes petit:  ',e24.16,'      2^(',i5,')')
      end
