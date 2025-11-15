// Proc: a

CCODE {
a:
    exec @blk_1 ;
    if @endif_1 ;
@thencode_1:
    exec @blk_2 ;
    ret ;
@endif_1:
    exec @blk_3 ;
    if @endif_2 ;
@thencode_2:
    exec @blk_4 ;
    call a 8 4 ;
    ret ;
@endif_2:
    exec @blk_5 ;
    call a 8 4 ;
    call a 8 4 ;
    ret ;
}


XCODE {
@blk_1:
    locpushd 0 ;
    imdpush 0 ;
    eq ;
@blk_2:
    locpushd 4 ;
    imdpush 1 ;
    add ;
    locpushd 8 ;
    add ;
@blk_3:
    locpushd 4 ;
    imdpush 0 ;
    eq ;
@blk_4:
    locpushd 0 ;
    imdpush 1 ;
    sub ;
    imdpush 1 ;
@blk_5:
    locpushd 0 ;
    imdpush 1 ;
    sub ;
    locpushd 0 ;
    locpushd 4 ;
    imdpush 1 ;
    sub ;
}

// Proc: main

CCODE {
main:
    exec @blk_6 ;
    ret ;
}


XCODE {
@blk_6:
    imdpush 0 ;
}

