      subroutine lorenz(n,t,x,y,rpar,ipar)
      implicit none
      integer*4 n,ipar
      real*8 t,x(3),y(3),rpar

      y(1)=10.d0*(x(2)-x(1))
      y(2)=x(1)*(28.d0-x(3))-x(2)
      y(3)=x(1)*x(2)-(8.d0*x(3))/3.d0

      return
      end
