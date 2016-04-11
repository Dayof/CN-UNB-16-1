program seno

    implicit none

    integer :: i, N
    real, dimension(25) :: v
    real :: pi

    N = 25

    pi = 4d0*datan(1d0)

    open(unit=1, file="list1-1.dat", status="unknown")

    do i=1, N
        v(i) = (i-1)*2.0*pi/(1.0*N)
        write(1, *) v(i), sin(v(i))
    end do

    close(unit=1)


end program 