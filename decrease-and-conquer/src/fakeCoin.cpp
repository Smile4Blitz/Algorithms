#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

/*
this function returns
-1: left weight > right weight
0: left weight = right weight
1: left weight < right weight
*/
int useBalance(std::vector<int> &left, std::vector<int> &right)
{
  int result_left = std::count(left.begin(), left.end(), 1);
  int result_right = std::count(right.begin(), right.end(), 1);

  if (result_left > result_right)
  {
    return -1;
  }
  if (result_left < result_right)
  {
    return 1;
  }
  return 0;
}

/* Function to determine the position of the fake coin in the array*/
int findFakeCoin(std::vector<int> &coins, int offset, int length)
{
  switch (length)
  {
  case 1:
    return offset;
  case 2:
    return (coins[offset] == 2) ? offset : offset + 1;
  }

  size_t v_size = length / 3;

  std::vector<int> l(coins.begin() + offset, coins.begin() + offset + v_size);
  std::vector<int> r(coins.begin() + offset + v_size, coins.begin() + offset + (v_size * 2));
  int res = useBalance(l, r);

  // case 1: l contains 2
  // case -1: r contains 2
  // case 0: remainder contains 2
  switch (res)
  {
  case 1:
    return findFakeCoin(coins, offset, v_size);
  case -1:
    return findFakeCoin(coins, offset + v_size, v_size);
  default:
    return findFakeCoin(coins, offset + (v_size * 2), length-(v_size*2));
  }
}

bool testFakeCoinProblem()
{
  for (int m = 90; m < 110; m++)
  {

    // make vector
    std::vector<int> coins(m, 1);
    coins.push_back(2); // adding faking coin
    for (int p = 0; p < 100; p++)
    {
      std::default_random_engine rng(time(0));
      std::shuffle(coins.begin(), coins.end(), rng);

      // Find it with the algorithms library
      int result = std::find(coins.begin(), coins.end(), 2) - coins.begin(); // TODO

      // Find it with decrease and conquer
      int result2 = findFakeCoin(coins, 0, coins.size());
      if (result2 != result)
        return false;
    }
  }
  return true;
}

int main()
{
  std::cout << "Test fake problem " << (testFakeCoinProblem() ? "succes" : "failed") << std::endl;
  return 0;
}