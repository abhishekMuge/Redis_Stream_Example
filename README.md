<h1 align="center" id="title">Redis_Stream_Example</h1>

<p align="center"><img src="https://socialify.git.ci/abhishekMuge/Redis_Stream_Example/image?language=1&amp;owner=1&amp;name=1&amp;stargazers=1&amp;theme=Light" alt="project-image"></p>

<h2>🛠️ Installation Steps:</h2>

<p>1. Compile Producer</p>

```
g++ -std=c++17 producer.cpp -o producer -lredis++ -lhiredis -lpthread
```

<p>2. Compile Consumer</p>

```
g++ -std=c++17 consumer.cpp -o consumer -lredis++ -lhiredis -lpthread
```
