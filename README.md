# pipex
### 42 project about reproducing the behaviour of the shell pipe '|'
The purpose of the project was to get familiar with pipelines, child processes and execution of commands.

The program is executed as:
```bash
$> ./pipex file1 cmd1 cmd2 file2
```
and behaves exactly the same as the shell command below:
```bash
$> < file1 cmd1 | cmd2 > file2
```
>For example: `< infile ls -l | wc -l > outfile`
