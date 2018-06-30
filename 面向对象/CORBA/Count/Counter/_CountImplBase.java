package Counter;
abstract public class _CountImplBase extends org.omg.CORBA.portable.Skeleton implements Counter.Count {
  protected _CountImplBase(java.lang.String name) {
    super(name);
  }
  protected _CountImplBase() {
  }
  public java.lang.String[] _ids() {
    return __ids;
  }
  private static java.lang.String[] __ids = {
    "IDL:Counter/Count:1.0"
  };
  public org.omg.CORBA.portable.MethodPointer[] _methods() {
    org.omg.CORBA.portable.MethodPointer[] methods = {
      new org.omg.CORBA.portable.MethodPointer("increment", 0, 0),
      new org.omg.CORBA.portable.MethodPointer("_set_sum", 0, 1),
      new org.omg.CORBA.portable.MethodPointer("_get_sum", 0, 2),
    };
    return methods;
  }
  public boolean _execute(org.omg.CORBA.portable.MethodPointer method, org.omg.CORBA.portable.InputStream input, org.omg.CORBA.portable.OutputStream output) {
    switch(method.interface_id) {
    case 0: {
      return Counter._CountImplBase._execute(this, method.method_id, input, output); 
    }
    }
    throw new org.omg.CORBA.MARSHAL();
  }
  public static boolean _execute(Counter.Count _self, int _method_id, org.omg.CORBA.portable.InputStream _input, org.omg.CORBA.portable.OutputStream _output) {
    switch(_method_id) {
    case 0: {
      int _result = _self.increment();
      _output.write_long(_result);
      return false;
    }
    case 1: {
      int sum;
      sum = _input.read_long();
      _self.sum(sum);
      return false;
    }
    case 2: {
      int _result = _self.sum();
      _output.write_long(_result);
      return false;
    }
    }
    throw new org.omg.CORBA.MARSHAL();
  }
}
