      subroutine pepe(n,t,x,y,rpar,ipar)
      implicit none
      integer*4 n,ipar
      real*8 t,x(2),y(2),rpar

      y(1)=x(2)
      y(2)=-dsin(x(1))-0.1d0*x(2)+0.1d0*dsin(t)

      return
      end
