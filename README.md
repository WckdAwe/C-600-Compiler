[![Contributors][contributors-shield]][contributors-url]
[![All Contributors](https://img.shields.io/badge/all_contributors-1-orange.svg?style=flat-square)](#contributors)
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]

<br />
<p align="center">
  <h1 align="center">C-600-Compiler</h3>

  <p align="center">
    A simple <b>semi-complete</b> compiler based on
    <br>
    a subset language rules of C++.
  </p>
</p>

## Table of Contents

- [Table of Contents](#table-of-contents)
- [About The Project](#about-the-project)
  - [Built with](#built-with)
- [Getting Started](#getting-started)
- [Roadmap](#roadmap)
- [Contributing ✨](#contributing-%e2%9c%a8)
- [Authors](#authors)
- [License](#license)
- [Disclaimer](#disclaimer)
- [Security](#security)
- [Acknowledgements](#acknowledgements)
- [Contributors ✨](#contributors-%e2%9c%a8)



<!-- ABOUT THE PROJECT -->

## About The Project

This compiler is based on a subset of language C++, created solely for a project assigned to us by [Professor G. Dimitriou][GDIMITRIOU] on the 5th Semester of [CS Dept., University of Thessaly][CSUTH]. (Subject INFS137-Compilers)

In no means we share this as an actual fully working compiler, but rather as the building blocks of a prototype compiler.

You can read more about the C++600 subset instructions (Greek Version Only!) under the [C++600.pdf][C++600.pdf].

### Built with
 - [Flex - Fast Lexical Analyzer](http://gnuwin32.sourceforge.net/packages/flex.htm)
 - [Bison - Yacc-compatible parser generator](http://gnuwin32.sourceforge.net/packages/bison.htm)
 - Plenty of C and pure love
 


<!-- GETTING STARTED -->

## Getting Started

We have separated our workload into 3 stages. Each stage contains execution instructions for the program accordingly, as well as some extra information that we decided to share for these stages.

See:
 - [Stage 1 - Lexical Analysis][STAGE1]
 - [Stage 2 - Syntax Analysis][STAGE2]
 - [Stage 3 - Semantics Analysis][STAGE3]

But **before proceeding to these steps**, make sure to have installed any dependencies such as **Flex** and **Bison**



<!-- ROADMAP -->

## Roadmap

There are currently **no plans for completing or expanding** the project by the original authors ([see below](#authors)). Nonetheless, any [contribution](#contributing) to the project is always welcome.

See the [open issues][issues-url] for a list of proposed features (and known issues).



<!-- Contributing -->

## Contributing ✨

Please read [CONTRIBUTING.md][CONTRIBUTING] for details on our code of conduct, and the process for submitting pull requests to us.

Thanks goes to these wonderful people ✨:
<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/TheNotoriousCS"><img src="https://avatars0.githubusercontent.com/u/31367091?v=4" width="100px;" alt="TheNotoriousCS"/><br /><sub><b>TheNotoriousCS</b></sub></a><br /><a href="https://github.com/WckdAwe/C-600-Compiler/commits?author=TheNotoriousCS" title="Code">💻</a> <a href="#content-TheNotoriousCS" title="Content">🖋</a></td>
  </tr>
</table>
<!-- ALL-CONTRIBUTORS-LIST:END -->

<!-- Authors -->

## Authors
- **Dimitriadis Vasileios** (WckdAwe) --  ( [Website]( http://wckdawe.com) | [Github](https://github.com/wckdawe) )
- **Kouskouras Taxiarchis** (TheNotoriousCS) -- ( [Github](https://github.com/TheNotoriousCS) )

And special thanks to [Papageorgiou Grigorios](https://github.com/TheFamousFurious) for providing the **Transition Diagram** for "Stage 2 - Syntax Analysis" and some other notable contributions in this project.


<!-- License -->

## License

This project is licensed under the MIT License - see the [LICENSE.md][LICENSE] file for details. 



<!-- Disclaimer -->

## Disclaimer

All the information on this repository is provided in good faith, however we make no representation or warranty of any kind, express or implied, regarding the accuracy, adequacy, validity, reliability, availability or completeness of any information - see the [DISCLAIMER.md][DISCLAIMER] file for more details.



<!-- Security -->

## Security

For security related issues please read [SECURITY.md][SECURITY].



<!-- ACKNOWLEDGEMENTS -->

## Acknowledgements

Hats off to any person whom contributed to this Project, formally or informally. This couldn't be possible without the assistance of these people.

- Professors [G. Dimitriou][GDIMITRIOU] and G. Floros
- Professor [Nikolas Papaspirou](https://www.ece.ntua.gr/gr/staff/71) for providing a more helpful Scope Library (Used in Stage 3)
- Github project [PASC320](https://github.com/nikolaskostakis/Pasc320-Compiler) by [nikolaskostakis](https://github.com/nikolaskostakis)
- Github project [Llama Compiler](https://github.com/ychatz/compiler) by [ychatz](https://github.com/ychatz)












<!-- C600 Github related links -->
[STAGE1]: https://github.com/WckdAwe/C-600-Compiler/tree/master/1.%20Lexical%20Analysis
[STAGE2]: https://github.com/WckdAwe/C-600-Compiler/tree/master/2.%20Syntax%20Analysis
[STAGE3]: https://github.com/WckdAwe/C-600-Compiler/tree/master/3.%20Semantics%20Analysis
[CONTRIBUTING]: https://github.com/WckdAwe/C-600-Compiler/blob/master/CONTRIBUTING.md
[SECURITY]: https://github.com/WckdAwe/C-600-Compiler/blob/master/SECURITY.md
[LICENSE]: https://github.com/WckdAwe/C-600-Compiler/blob/master/LICENSE.md
[DISCLAIMER]: https://github.com/WckdAwe/C-600-Compiler/blob/master/DISCLAIMER.md



<!-- Helpful Links & People -->
[CSUTH]: http://cs.uth.gr/
[GDIMITRIOU]: https://www.e-ce.uth.gr/department/faculty/dimitriu/
[C++600.pdf]: https://github.com/WckdAwe/C-600-Compiler/blob/master/c%2B%2B600.pdf

<!-- othneildrew's Best-README-Template -->
[contributors-shield]: https://img.shields.io/github/contributors/WckdAwe/C-600-Compiler.svg?style=flat-square
[contributors-url]: https://github.com/WckdAwe/C-600-Compiler/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/WckdAwe/C-600-Compiler.svg?style=flat-square
[forks-url]: https://github.com/WckdAwe/C-600-Compiler/network/members
[stars-shield]: https://img.shields.io/github/stars/WckdAwe/C-600-Compiler.svg?style=flat-square
[stars-url]: https://github.com/WckdAwe/C-600-Compiler/stargazers
[issues-shield]: https://img.shields.io/github/issues/WckdAwe/C-600-Compiler.svg?style=flat-square
[issues-url]: https://github.com/WckdAwe/C-600-Compiler/issues
[license-shield]: https://img.shields.io/github/license/WckdAwe/C-600-Compiler.svg?style=flat-square
[license-url]: https://github.com/WckdAwe/C-600-Compiler/blob/master/LICENSE.md
## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore -->
<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!