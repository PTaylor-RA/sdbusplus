# net.poettering.Calculator

An example interface originally described as part of the announcment of new sd-bus interfaces at:
    http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html


## Methods
### Multiply

Multiplies two integers 'x' and 'y' and returns the result.


#### Parameters and Returns
| direction | name | type | description |
|:---------:|------|------|-------------|
| in | **x** | int64 | The first integer to multiply. |
| in | **y** | int64 | The second integer to multiply. |
| out | **z** | int64 | The result of (x*y). |


### Divide

Divides two integers 'x' and 'y' and returns the result.


#### Parameters and Returns
| direction | name | type | description |
|:---------:|------|------|-------------|
| in | **x** | int64 | The first integer to divide. |
| in | **y** | int64 | The second integer to divide. |
| out | **z** | int64 | The result of (x/y). |

#### Errors
 * self.Error.DivisionByZero

### Clear

Reset the LastResult property to zero.





## Properties
| name | type | description |
|------|------|-------------|
| **LastResult** | int64 | The result of the most recent calculation. |
| **Status** | enum[self.State] | The current state of the Calculator. |

## Signals
### Cleared

Signal indicating the LastReset property has been set to zero by the 'Clear' method.


#### Properties
| name | type | description |
|------|------|-------------|
| **unnamed** | int64 | Value of LastReset prior to Clear. |


## Enumerations
### State

Identifies if the service has encountered an error or not.


| name | description |
|------|-------------|
| **Success** | No error has been encountered. |
| **Error** | The service has encountered an error. |

## Errors

### DivisionByZero

An attempt to divide by zero was attempted.


