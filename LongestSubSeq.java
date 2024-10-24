public class LongestSubSeq implements Runnable
{
  public class State
  {
    int idx = -1;
    int n = -1;
    int c = -1;
  }


  public State current_state;
  public int left, right;
  public int array[];


  LongestSubSeq(int org_arr[], int l, int r) 
  {
    this.array = org_arr;
    this.left = l;
    this.right = r;
    current_state = new State();
  }


  public void merge(State left, State right)
  {
    /* Left bigger than right */
    if (left.n >= right.n) 
    {
      current_state.n = left.n;
      current_state.idx = left.idx;
      current_state.c = left.c;
    }
    /* Right bigger than left */
    else
    {
      current_state.n = right.n;
      current_state.idx = right.idx;
      current_state.c = right.c;
    }

    /* Both have the same letter, thus check if they merge */
    if (left.c == right.c && left.idx + left.n == right.idx)
    {
      current_state.idx = left.idx;
      current_state.n = left.n + right.n;
      current_state.c = left.c;
    }

    /* Now we gonna check strip between the two */
    int strip_idx = -1;
    int strip_n = -1;
    int strip_c = -1;

    /* This is our result (if better than current) */
    int best_idx = -1;
    int best_n = -1;
    int best_c = -1;

    for (int i = left.idx + left.n; i < right.idx + right.n; ++i)
    {
      /* Edge case for first iteration */
      if (i == left.idx + left.n)
      {
        strip_idx = i;
        strip_n = 1;
        strip_c = array[strip_idx];
      }
      else
      {
        /* If mismatch, reset it */
        if (array[i] != strip_c)
        {
          strip_idx = i;
          strip_n = 1;
          strip_c = array[i];
        }
        else
        {
          strip_n += 1;
        }
        /* If better now, save it */
        if (strip_n > best_n)
        {
          best_idx = strip_idx;
          best_n = strip_n;
          best_c = strip_c;
        }
      }
    }



    /* If there is better sub sequence on strip, save it */
    if (best_n > current_state.n)
    {
      current_state.n = best_n;
      current_state.idx = best_idx;
      current_state.c = best_c;
    }
  }


  @Override
  public void run()
  {
    /* Recursive stop */
    if (left == right)
    {
      current_state.idx = left;
      current_state.c = array[left];
      current_state.n = 1;
      return;
    }

    /* Divide & Conquer */
    int middle = (left + right) / 2;

    LongestSubSeq left_rec = new LongestSubSeq(array, left, middle);
    LongestSubSeq right_rec = new LongestSubSeq(array, middle + 1, right);

    Thread thread1 = new Thread(left_rec);
    Thread thread2 = new Thread(right_rec);

    thread1.start();
    thread2.start();

    try 
    {
      thread1.join();
      thread2.join();
    }
    catch (InterruptedException e)
    {
      e.printStackTrace();
    }

    merge(left_rec.current_state, right_rec.current_state);
  }

  public static void main(String[] args)
  {
    int array1[] = {1, 2, 1, 2, 1, 2, 1, 2, 3, 3, 3};
    int array2[] = {3, 3, 3, 2, 3, 3};

    LongestSubSeq sub1 = new LongestSubSeq(array1, 0, array1.length - 1);
    LongestSubSeq sub2 = new LongestSubSeq(array2, 0, array2.length - 1);

    Thread job1 = new Thread(sub1);
    Thread job2 = new Thread(sub2);

    job1.start();
    job2.start();

    try
    {
      job1.join();
      job2.join();
    }
    catch (InterruptedException e)
    {
      e.printStackTrace();
    }

    System.out.printf("i=%d, n=%d, val=%d\n", 
                   sub1.current_state.idx, sub1.current_state.n, sub1.current_state.c);

    System.out.printf("i=%d, n=%d, val=%d\n", 
                   sub2.current_state.idx, sub2.current_state.n, sub2.current_state.c);
  }
}
