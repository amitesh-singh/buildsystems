project('avrbuild', 'c')

mystrip = find_program('avr-strip')


#striptarget = custom_target('do-strip',
#              #input: '',
#              output: 'blinkstripped',
#              command: [mystrip, '@INPUT@', '@OUTPUT@'],
#             )
#run_target(striptarget)

cargs =        ['-Os',
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
linkargs =      ['-Wl,-Map,blink.map',
                 '-Wl,--gc-sections',
                 '-Wl,--relax',
                 '-mmcu=attiny13a'
                ]

exe = executable('blink', 'blink.c',
           c_args: cargs,
           link_args: linkargs
           )

message(exe.full_path())
#error('hello world')
stripbuild = run_target('stripp', command: [mystrip, (exe.full_path())], depends: exe)
mysize = find_program('avr-size')

run_target('size', command: [mysize, exe.full_path(), '--mcu=attiny13a -C --format=avr'], depends: exe)

myobjcmd = find_program('avr-objcopy')
run_target('objcopy-prepare', command: [myobjcmd, ['-O', 'ihex', '-j', '.eeprom', '--set-section-flags=.eeprom=alloc,load', '--no-change-warnings', 
                                                   '--change-section-lma', '.eeprom=0', exe.full_path(), exe.full_path() + '.eep']])
run_target('objcopy', command: [myobjcmd, ['-O', 'ihex', '-R', '.eeprom', exe.full_path(), exe.full_path() + '.hex']])

