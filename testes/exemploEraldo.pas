program test;

var
  x, y: integer;
  { .common _x, 4, 4
    .common _y, 4, 4}
  z, w: real;
  { .common _z, 4, 4
    .common _w, 4, 4}

function

    A (w: integer; var b: real): real;
    { _A:
      # w -> 8(%ebp)
      # &b -> 12(%ebp)}
    var x, t: real;
    { x -> -4(%ebp)
      t -> -8(%ebp)}
        v: array [16384] of double;
        { v -> -16(%ebp) -> $.A1
          .common .A1, 16384*8, 8
          ....
          movl $.A1, -16(%ebp)
          ....
          # v[i] := 0x8000235f00d00000
             movl -16(%ebp), %ecx
             movl _i, %eax
             mull $8
             addl %eax, %ecx
             movq 0x8000235f00d00000, (%ecx)}
    begin
      x := a*(y + z);
      t := w * b*(z - y);
      A := x * t
    end;

var
    b: array [1024] of array [256] of double;
    { .common _b, 1024*256*8, 8}
    c: array [4096] of integer;
    { .common _c, 4096*4, 4}

procedure D (a: real; var b: double);
    var
      x, y, z: double;

    begin { procedure D starts here }
      b := a * ( x + y + z )
    end;

begin { main program }
  x := y * (z + w);
  z := x - y * A;
  w := x + y
end.
