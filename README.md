# configEditor
It is realy simple config editor written as recruitment job, I guess It could been done better.

### Instalation
1. Download this repository by using command
`git clone https://github.com/anteczko/configEditor`
2. Get into folder
`cd configEditor`
3. Change program file permission
`chmod +x ./edit`
4. Run it
`./edit`

### Usage
By default program loads variables from config file and also checks their value correctness. Is value in file isn't correct il loads it anyway, but gives you feedback about what value is expected for this variable.

#### Paramaters
To change variable value run
```
edit -variableName <newValue>
edit -isLed true
```
You can also change multiple variables at once, and in any order
`edit -isLed false -numberOfPixels 2137`
String variable, suports spaces and other special character
`edit -nameOfProduct 'it's linux terminal co remember about quotes!!!' `
