program arcsen
    implicit none

    integer :: i, N
    real, dimension(:), allocatable :: x, s, arcs

    N = 25
    allocate(x(N))
    allocate(s(N))
    allocate(arcs(N))

    open(unit=2, file="list1-1.dat", status='unknown')

    do i=1, N 
        read(2,*) x(i), s(i) 
        arcs(i) = asin(s(i))
    end do

    call fseek(2,0,0)
    print *, ftell(2), 0

    do i=1, N 
        write(2,*) x(i), s(i), arcs(i)
    end do

    close(unit=2)

end program arcsen