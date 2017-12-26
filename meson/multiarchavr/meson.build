project('avrbuild', 'c')

mystrip = find_program('avr-strip')
mysize = find_program('avr-size')
myobjcmd = find_program('avr-objcopy')

#striptarget = custom_target('do-strip',
#              #input: '',
#              output: 'blinkstripped',
#              command: [mystrip, '@INPUT@', '@OUTPUT@'],
#             )
#run_target(striptarget)

attiny13acargs =['-Os',
                '-g',
                '-std=gnu99',
                '-Wall',
                '-funsigned-char',
                '-funsigned-bitfields',
                '-fpack-struct',
                '-fshort-enums',
                '-ffunction-sections',
                '-fdata-sections',
                '-DF_CPU=9600000UL',
                '-mmcu=attiny13a'
                    ]
attiny13alinkargs =      ['-Wl,-Map,blink.map',
                 '-Wl,--gc-sections',
                 '-Wl,--relax',
                 '-mmcu=attiny13a'
                ]

attiny85cargs = ['-Os',
                '-g',
                '-std=gnu99',
                '-Wall',
                '-funsigned-char',
                '-funsigned-bitfields',
                '-fpack-struct',
                '-fshort-enums',
                '-ffunction-sections',
                '-fdata-sections',
                '-DF_CPU=9600000UL',
                '-mmcu=attiny85'
                ]
attiny85linkargs =      ['-Wl,-Map,blink.map',
                 '-Wl,--gc-sections',
                 '-Wl,--relax',
                 '-mmcu=attiny85'
                ]

progs = [['blink1', 'blink.c', attiny13acargs, attiny13alinkargs, '--mcu=attiny13a'],
         ['blink2', 'blink.c', attiny85cargs, attiny85linkargs, '--mcu=attiny85']
        ]

foreach p : progs

    exe = executable(p[0], p[1],
               c_args: p[2],
               link_args: p[3],
               build_by_default: true)

    test(p[0], exe)
    message(exe.full_path())
    custom_target(p[0] + '-' + 'makehex',
                  input: exe.full_path(),
                  output: p[0] + '.hex',
                  command: [myobjcmd,'-O', 'ihex', '-R', '.eeprom', '@INPUT@', '@OUTPUT@'], depends: exe,
                  build_always : false
                 )
    
    run_target(p[0] + '-' +'eep', command: [myobjcmd, ['-O', 'ihex', '-j', '.eeprom', '--set-section-flags=.eeprom=alloc,load', '--no-change-warnings', 
                                                  '--change-section-lma', '.eeprom=0', exe.full_path(), exe.full_path() + '.eep']], depends: exe)
    run_target(p[0] + '-' +'hex', command: [myobjcmd, ['-O', 'ihex', '-R', '.eeprom', exe.full_path(), exe.full_path() + '.hex']], depends: exe)
    run_target(p[0] + '-' +'size', command: [mysize, exe.full_path(), p[4] + ' -C --format=avr'], depends: exe)

endforeach




