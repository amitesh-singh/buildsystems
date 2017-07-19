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
run_target('stripp', command: [mystrip, (exe.full_path())], depends: exe)

