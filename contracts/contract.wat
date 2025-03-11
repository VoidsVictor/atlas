(module
  (func $contract (export "contract") (param $n i32) (result i32)
    ;; if n < 2 then return n, else return fib(n-1) + fib(n-2)
    (if (result i32)
      (i32.lt_s (local.get 0) (i32.const 2))
      (then 
        (local.get 0)
      )
      (else 
        (i32.add
          (call $contract (i32.sub (local.get 0) (i32.const 1)))
          (call $contract (i32.sub (local.get 0) (i32.const 2)))
        )
      )
    )
  )
)
