      program mainpepe
      implicit none
      real*8 t,tf,x(2),work(93),rpar,erel,eabs,e,ee
      integer*4 lwork,liwork,iwork(39),ipar,idid,j
      external pepe,solout

      erel=1.d-16
      eabs=erel

      lwork=93
      liwork=39

      do 1 j=1,lwork
 1       work(j)=0.d0
      do 2 j=1,liwork
 2       iwork(j)=0

      do 10 j=1,999
         x(1)=0.d0
         x(2)=0.d0

         t=0.d0
         tf=16.d0
         call dop853(2,pepe,t,x,tf,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
 10      continue

      x(1)=0.d0
      x(2)=0.d0

      t=0.d0
      tf=16.d0
      call dop853(2,pepe,t,x,tf,erel,eabs,0,solout,0,work,lwork,
     @             iwork,liwork,rpar,ipar,idid)
      write(6,*) ' idid:',idid

      e=dabs(x(1)-0.53752534081134067261d0)
      ee=dabs(x(2)+0.12104140610381475352d0)
      if (ee.gt.e) e=ee

      write(6,600) e

      stop
 600  format(' error:',d15.6)
      end
      subroutine solout()
      return
      end
