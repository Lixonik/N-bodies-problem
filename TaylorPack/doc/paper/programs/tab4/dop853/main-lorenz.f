      program mainlorenz
      implicit none
      real*8 t,tf,x(3),work(107),rpar,erel,eabs,e,ee
      integer*4 lwork,liwork,iwork(39),ipar,idid,j,k
      external lorenz,solout

      erel=1.d-16
      eabs=erel

      lwork=107
      liwork=39

      do 1 k=1,lwork
 1       work(k)=0
      do 2 k=1,liwork
 2         iwork(k)=0

      do 10 j=1,999
         x(1)=-8.d0
         x(2)= 8.d0
         x(3)=27.d0

         t=0.d0
         tf=16.d0
         call dop853(3,lorenz,t,x,tf,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
 10      continue

      x(1)=-8.d0
      x(2)= 8.d0
      x(3)=27.d0

      t=0.d0
      tf=16.d0
      call dop853(3,lorenz,t,x,tf,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
      write(6,*) ' idid:',idid

      e=dabs(x(1)+9.13131302736875292786)
      ee=dabs(x(2)+12.47617881107825333392)
      if (ee.gt.e) e=ee
      ee=dabs(x(3)-22.84333896098238820550)
      if (ee.gt.e) e=ee

      write(6,600) e

      stop
 600  format(' error:',d15.6)
      end
      subroutine solout()
      return
      end
