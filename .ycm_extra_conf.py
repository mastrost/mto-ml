def Settings( **kwargs ):
    filename=kwargs['filename']
    if(filename.endswith(".c")):
        return {
                'flags': 
                [ '-x', 'c', '-Wall', '-Werror'
                 , '-Werror=missing-field-initializers'
                 , "-Wimplicit-fallthrough"
                 , "-DCHECK_PRECONDITIONS"
                 , "-DIDE"
                 , '-I', '.'
                 ],
                }
    else:
        return {
                'flags': 
                [ '-x', 'c++', '-Wall', '-Werror', '-std=c++20'
                 , '-Werror=missing-field-initializers'
                 , "-Wimplicit-fallthrough"
                 , '-Wno-unused-local-typedef'
                 , "-DCHECK_PRECONDITIONS"
                 , "-DIDE"
                 , '-I', '.'
                 ],
                }
