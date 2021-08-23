# Corctf babyrev writeup

### Description
well uh... this is what you get when you make your web guy make a rev chall

### Points
372

### Solves
203

### Body (TLDR at bottom)

Upon downloading the file I unzipped it and found the challenge file named `babyrev`

running `file` showed that it was an ELF 64 bit pie executable
![image of terminal showing file command](https://i.imgur.com/vIUEmp6.png)

With that my first thought was to run `strings babyrev | grep corctf` to see if anything came up
![image of running strings](https://i.imgur.com/J3Mx0GW.png)

and something did come up!

But after further inspection there didn't seem to be much info as far as the flag goes, so I had to spend some more time digging deeper.

At this point I opened Ghidra and went into the main function to see if I could figure out some of the logic.

I spent a bit of time renaming variables in the C code Ghidra generated to try to make sense of it and this is what I came up with.

![Image of ghidra C code](https://i.imgur.com/P9ngNtC.png)

At this point I was able to determine the main logic of the function.

First the program checks to make sure the input is the right length and contains `corctf{` at the beginning.  Then it would take your input and strip off the `corctf{` and `}` from the front and back.

Then the program would generate a prime number for each index of the input string.
The prime number was decided as `index * 4 and increment by 1 until it is prime`

This prime number was then fed in as an argument to the rot_n method that would decode input and compare this coded input to `check` that was in the program memory.

I noticed that `check` was being loaded from the program's memory then passed through `memfrob()` to decode it.  After some research I found `memfrob()` was just an XOR42 algorithm so it was reversible by simply putting it through the algorithm again.

So I found the `check` data within the program's memory

![image of check data](https://i.imgur.com/G27Xz6x.png)

I spent a decent amount of time trying to write a reverse algorithm to the rot_n with the prime offset but for some reason I just wasn't finding success.  At that point one of my teammates suggested that with the information I had I could probably just brute force it.

So I wrote a C script to generate the prime numbers, and XOR42 for the `check` data.

Then the script would simply guess inputs for the rot_n until it matched the XOR42 decoded `check` data.

That did it!
```
int check[20] = {0x5f,0x40,0x5a,0x15,0x75,0x45,0x62,0x53,0x75,0x46,0x52,0x43,0x5f,0x75,0x50,0x52,0x75,0x5f,0x5c,0x4f};

int primes[20] = {2, 5, 11, 13, 17, 23, 29, 29, 37, 37, 41, 47, 53, 53, 59, 61, 67, 71, 73, 79};
int test[20];// = {117,106,112,63,95,111,72,121,95,108,120,105,117,95,95,122,120,95,117,118};
int test_result[20];


int main()
{

    for (int i = 0; i < 20; i++)
    {
        test[i] = check[i] ^ 42;
    }

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if (rot_n(j,primes[i]) == test[i])
            {
                test_result[i] = j;
                printf("%c",(char)j);
            }
        }
    }
    return 0;
}
```
```
┌──(kali㉿kali)-[~/Downloads/corCTF/babyrev]
└─$ ./brute  
see?_rEv_aint_so_bad  
```

flag : `corctf{see?_rEv_aint_so_bad}`

TLDR: Flag was decoded with XOR42 in the program's source.  Used this knowledge along with the ROT_N algorithm in the source to brute force the solution.
