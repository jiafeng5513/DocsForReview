package Counter;
public class _st_Count extends org.omg.CORBA.portable.ObjectImpl implements Counter.Count {
  public java.lang.String[] _ids() {
    return __ids;
  }
  private static java.lang.String[] __ids = {
    "IDL:Counter/Count:1.0"
  };
  public int increment() {
    try {
      org.omg.CORBA.portable.OutputStream _output = this._request("increment", true);
      org.omg.CORBA.portable.InputStream _input = this._invoke(_output, null);
      int _result;
      _result = _input.read_long();
      return _result;
    }
    catch(org.omg.CORBA.TRANSIENT _exception) {
      return increment();
    }
  }
  public void sum(int sum) {
    try {
      org.omg.CORBA.portable.OutputStream _output = this._request("_set_sum", true);
      _output.write_long(sum);
      org.omg.CORBA.portable.InputStream _input = this._invoke(_output, null);
    }
    catch(org.omg.CORBA.TRANSIENT _exception) {
      sum(
        sum
      );
    }
  }
  public int sum() {
    try {
      org.omg.CORBA.portable.OutputStream _output = this._request("_get_sum", true);
      org.omg.CORBA.portable.InputStream _input = this._invoke(_output, null);
      int _result;
      _result = _input.read_long();
      return _result;
    }
    catch(org.omg.CORBA.TRANSIENT _exception) {
      return sum();
    }
  }
}
