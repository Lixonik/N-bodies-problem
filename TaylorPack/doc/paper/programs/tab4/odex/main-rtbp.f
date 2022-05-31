      program mainrtbp
      implicit none
      real*8 t,tf,h,x(6),work(149),rpar,erel,eabs,e,ee
      integer*4 j,lwork,liwork,iwork(39),ipar,idid
      external rtbp,solout

      erel=1.d-16
      eabs=erel

      lwork=149
      liwork=39

      do 1 j=1,lwork
 1       work(j)=0
      do 2 j=1,liwork
 2       iwork(j)=0
      h=1.d-2

      do 10 j=1,999
         x(1)=-0.45d0
         x(2)= 0.80d0
         x(3)= 0.00d0
         x(4)=-0.80d0
         x(5)=-0.45d0
         x(6)= 0.58d0

         t=0.d0
         tf=16.d0
         call odex(6,rtbp,t,x,tf,h,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
 10      continue

      x(1)=-0.45d0
      x(2)= 0.80d0
      x(3)= 0.00d0
      x(4)=-0.80d0
      x(5)=-0.45d0
      x(6)= 0.58d0

      t=0.d0
      tf=16.d0
      call odex(6,rtbp,t,x,tf,h,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
      write(6,*) ' idid:',idid

      e=dabs(x(1)+0.56210340265552085504d0)
      ee=dabs(x(2)-0.87742260648445467260d0)
      if (ee.gt.e) e=ee
      ee=dabs(x(3)+0.22370669045517274593d0)
      if (ee.gt.e) e=ee
      ee=dabs(x(4)+0.61230928495937399217d0)
      if (ee.gt.e) e=ee
      ee=dabs(x(5)+0.51125245057813111131d0)
      if (ee.gt.e) e=ee
      ee=dabs(x(6)+0.45728848688565667119d0)
      if (ee.gt.e) e=ee

      write(6,600) e

      stop
 600  format(' error:',d15.6)
      end
      subroutine hamilton(x,h)
      implicit none
      real*8 x(6),h,mu,r2,a,b,c,d
      parameter (mu=0.01d0)

      r2=x(1)*x(1)+x(2)*x(2)+x(3)*x(3)
      a=r2-2*mu*x(1)+mu*mu
      b=r2+2*(1-mu)*x(1)+(1-mu)*(1-mu)
      c=x(2)*x(4)-x(1)*x(5)
      d=x(4)*x(4)+x(5)*x(5)+x(6)*x(6)
      h=0.5d0*d+c-(1-mu)/sqrt(a)-mu/sqrt(b)

      return
      end
      subroutine solout()
      return
      end
