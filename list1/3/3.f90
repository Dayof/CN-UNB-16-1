program ordsin
    implicit none

    integer :: i, j
    integer, parameter :: N = 25
    real, dimension(25) :: x, s
    real :: temp
    
    open(unit=1,file="list1-1.dat",status="old",action='read')
        read(1,*) x(1), s(1)
        do i=2, N
            j=i-1
            read(1,*) x(i), s(i)
            temp = s(i)
            
            do while ((s(j).gt.temp).and.(j.ge.1))
                s(j+1) = s(j)
                j=j-1
            end do

            s(j+1)=temp
        end do
    close(unit=1)

    open(unit=2, file="list1-3.dat", status="unknown")
        do i=1, N
            write(2,*) i, s(i)
        end do
    close(unit=2)

end program ordsin
