// CountImpl.java: The Count Implementation
class CountImpl extends Counter._CountImplBase
{
  private int sum;

  // Constructors
  CountImpl(String name)
  { super(name);
    System.out.println("Count Object Created");
    sum = 0;
  }

  // get sum
  public  int sum()
  { return sum;
  }

  // set sum
  public  void sum(int val)
  { sum = val;
  }

  // increment method
  public int increment()
  { sum++;
    return sum;
  }
}
