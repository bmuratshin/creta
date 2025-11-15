DATA {
        a: 0x0001;
        b: 0x0002;
}

CCODE {
@initial:
        exec block1;
        call factorial 4 0;
}
CCODE {
factorial:
        exec block2;
        if @endif1;
        exec block3;
        ret;
@endif1:
        exec block4;
        call factorial 4 0;
        exec block5;
        ret;
}

XCODE {
block1:
        imdpush 6;
        stop;

block2:
        imdpush 1;
        locpush 0;
        eval;
        cmp 2;
        stop;

block3:
        imdpush 1;
        stop;

block4:
        locpush 0;
        eval;
        imdpush 1;
        sub;
        stop;

block5:
        locpush 0;
        eval;
        mul;
        stop;
}

DATA {
        c: 0x0003;
        d: 0x0004;
}
