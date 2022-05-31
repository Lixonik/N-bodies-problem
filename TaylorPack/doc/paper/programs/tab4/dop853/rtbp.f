      subroutine rtbp(n,t,x,y,rpar,ipar)
      implicit none
      integer*4 n,ipar
      real*8 t,x(6),y(6),r2,mu,d,e,f,rpe2,rpm2,rpe3i,rpm3i,rpar
      parameter (mu=0.01d0)

      r2=x(1)*x(1)+x(2)*x(2)+x(3)*x(3)
      rpe2=r2-2.d0*mu*x(1)+mu*mu
      rpe3i=1.d0/sqrt(rpe2*rpe2*rpe2)
      rpm2=r2+2.d0*(1.d0-mu)*x(1)+(1.d0-mu)*(1.d0-mu)
      rpm3i=1.d0/sqrt(rpm2*rpm2*rpm2)
      d=(1.d0-mu)*rpe3i
      e=mu*rpm3i
      f=d+e

      y(1)=x(4)+x(2)
      y(2)=x(5)-x(1)
      y(3)=x(6)
      y(4)=x(5)-(x(1)-mu)*d-(x(1)+(1.d0-mu))*e
      y(5)=-x(4)-x(2)*f
      y(6)=-x(3)*f
      return
      end
