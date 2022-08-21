import inspect

class IStringWriter:
    def write(self, string: str):
        pass

class MyStringWriter(IStringWriter):
    pass

# i can use MyStringWriter even though the class doesn't override write
writer = MyStringWriter()

def checkIfSignaturesAreCompatible(sig1, sig2):
    sig1_params = [p for p in sig1.parameters.values()]
    sig2_params = [p for p in sig2.parameters.values()]
    
    if len(sig1_params) != len(sig2_params):
        return False
    
    if len(sig1_params) != 0 and (sig1_params[0].name == 'self') ^ (sig2_params[0].name == 'self'):
        return False
    
    for i in range(len(sig1_params)):
        p1 = sig1_params[i]
        p2 = sig2_params[i]
    
        if p1.annotation != inspect.Parameter.empty and p2.annotation != inspect.Parameter.empty:
            if p1.annotation != p2.annotation:
                return False
    return True

class InterfaceImpl(type):
    def __init__(self, name, bases, dct):
        for base in bases:
            base_name = base.__name__
            if base_name[0] != 'I' or len(base_name) == 1 or base_name[1].islower():
                continue
            methods = [*filter(lambda x: not x.startswith('__') and not x.endswith('__'), dir(base))]
            for method_name in methods:
                method = getattr(base, method_name)
                method_sig = inspect.signature(method)
                
                assert method_name in dct, f"{name} doesn't implement {base_name}.{method_name}"
                cls_method = getattr(self, method_name)
                assert callable(cls_method), f"{name}.{cls_method} isn't a callable object"
                cls_method_sig = inspect.signature(cls_method)
                
                assert checkIfSignaturesAreCompatible(cls_method_sig, method_sig), f"{self.__name__}.{method_name}{cls_method_sig} doesn't match signature {base.__name__}.{method_name}{method_sig}"

            return super(InterfaceImpl, self).__init__(name, bases, dct)

#class MyNewStringWriter(IStringWriter, metaclass=InterfaceImpl):
#    pass
#writer = MyNewStringWriter()

#class MyNewStringWriter2(IStringWriter, metaclass=InterfaceImpl):
#    def write(self, hihi: str, haha: str):
#        print('write in MyNewStringWriter2: ', fds)
#    def hihi(self):
#        pass
#writer = MyNewStringWriter2()

#class MyNewStringWriter3(IStringWriter, metaclass=InterfaceImpl):
#    def write(self, houhou: bool):
#        print('write in MyNewStringWriter3: ', houhou)
#writer = MyNewStringWriter3()

#class MyNewStringWriter4(IStringWriter, metaclass=InterfaceImpl):
#    def write(gfd: str, **kwargs):
#        print('write in MyNewStringWriter5: ', kwargs['string'])
#writer = MyNewStringWriter4()

#class MyNewStringWriter5(IStringWriter, metaclass=InterfaceImpl):
#    write = 91
#writer = MyNewStringWriter5()

class MyNewStringWriter6(IStringWriter, metaclass=InterfaceImpl):
    def write(self, text):
        print('write in MyNewStringWriter6: ', str(text))
writer = MyNewStringWriter6()
writer.write("works")

class Icon:
    def on_hover(self):
        pass
class AnimatedIcon(Icon, metaclass=InterfaceImpl):
    pass
icon = AnimatedIcon()

#class ICon:
#    def on_hover(self):
#        pass
#class AnimatedIcon(ICon, metaclass=InterfaceImpl):
#    pass
#icon = AnimatedIcon()

