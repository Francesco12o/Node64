# 🚀 NodeOS — Node.js as PID 1

![NodeOS](https://img.shields.io/badge/NodeOS-JavaScript--based%20OS-339933?style=for-the-badge&logo=node.js&logoColor=white)
![Runtime](https://img.shields.io/badge/Runtime-Node.js-43853D?style=for-the-badge&logo=node.js&logoColor=white)
![Philosophy](https://img.shields.io/badge/Philosophy-REPL--First-3178C6?style=for-the-badge)
![Shell](https://img.shields.io/badge/Traditional%20Shell-Optional-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-See%20Upstream-lightgrey?style=for-the-badge)

**NodeOS is an operating-system project built around JavaScript and Node.js.** Its central idea is to bring Node.js into the operating system's userspace and make JavaScript a primary way to interact with the system.

Instead of treating a conventional Unix shell as the main interface, NodeOS explores an environment where Node.js and its package ecosystem are fundamental parts of the user experience.

> 💡 **Core philosophy:** Node.js is not merely an application running on the operating system. In the NodeOS design, Node.js can serve as PID 1 and provide the primary interactive JavaScript environment.

---

## 📖 Table of Contents

- [✨ Overview](#-overview)
- [🧠 Philosophy](#-philosophy)
- [⚙️ How It Works](#️-how-it-works)
- [💻 The Node.js REPL](#-the-nodejs-repl)
- [📦 Commands and Packages](#-commands-and-packages)
- [🐚 What About NSH?](#-what-about-nsh)
- [🛠️ Development](#️-development)
- [⚠️ Compatibility](#️-compatibility)
- [🔗 Resources](#-resources)

---

## ✨ Overview

NodeOS takes a JavaScript-first approach to operating-system design.

Its original project ecosystem includes:

- 🟢 **Node.js** — the JavaScript runtime at the center of userspace.
- 📟 **Node.js REPL** — an interactive environment for evaluating JavaScript.
- 📦 **npm packages** — an ecosystem for extending system functionality.
- 🧰 **NodeOS utilities** — programs and packages that provide operating-system functionality.
- 🐚 **NSH** — a shell environment available in the NodeOS ecosystem, rather than the only possible interface.

NodeOS is an experimental and historically significant project exploring how far a JavaScript runtime and its package ecosystem can be used to build a complete operating-system environment.

## 🧠 Philosophy

### 1. Node.js as PID 1

On a conventional Linux system, PID 1 is usually an init system such as systemd, OpenRC's init, or another process supervisor.

NodeOS explores a different approach: running Node.js as PID 1.

```text
Traditional Linux:

Linux Kernel
    └── Init System (PID 1)
          └── Login Shell
                └── Commands


NodeOS Concept:

Linux Kernel
    └── Node.js (PID 1)
          └── JavaScript Environment
                └── JavaScript Programs
```

This is a conceptual overview, not a guarantee that every NodeOS build uses precisely the same process tree.

### 2. JavaScript as the primary interface

A JavaScript-first operating system does not need to make a conventional shell the center of the experience.

The Node.js REPL provides an interactive prompt where users can evaluate expressions, inspect objects, call functions, and experiment with JavaScript.

### 3. Extendability through npm

Node.js already has a large package ecosystem. NodeOS builds on that ecosystem to provide system utilities and application functionality through JavaScript packages.

However, npm packages do not automatically have operating-system privileges or access to every system resource. Their capabilities depend on the runtime, permissions, and available system interfaces.

### 4. A shell is a tool, not the philosophy

A conventional shell can still be useful for command-oriented workflows, scripting, and compatibility with familiar tools.

But the existence of a shell does not define the core NodeOS concept. The central idea is the use of Node.js and JavaScript as foundational parts of userspace.

---

## ⚙️ How It Works

NodeOS combines a Linux kernel with a userspace environment built around Node.js.

At a high level:

1. 🖥️ **The kernel boots.** The kernel initializes hardware and provides fundamental operating-system services.
2. 🟢 **Node.js starts.** In the PID 1 design, Node.js becomes the first userspace process.
3. 📟 **An interactive interface becomes available.** A build configured for REPL-first operation can expose the Node.js console directly.
4. 📦 **JavaScript programs provide functionality.** Applications and utilities can use Node.js APIs and supported packages.
5. 🔧 **The environment can be extended.** Additional software can be integrated through the project's supported package and build mechanisms.

The exact boot process, available APIs, supported packages, and startup behavior depend on the particular NodeOS build.

---

## 💻 The Node.js REPL

The native Node.js REPL is the desired interface for a REPL-first NodeOS environment.

It looks like this:

```text
Welcome to Node.js v22.23.0.
Type ".help" for more information.
>
```

The version above is an illustrative example of the desired interface, not a claim about the Node.js version included in an original NodeOS release.

### Example JavaScript session

```javascript
> 1 + 1
2

> console.log("Hello from NodeOS!")
Hello from NodeOS!
undefined

> process.version
'v22.23.0'

> typeof process
'object'
```

The REPL evaluates JavaScript directly. It does not need to reinterpret every input as a shell command.

### Native REPL features

The standard Node.js REPL supports:

| Feature | Description |
|---|---|
| Expressions | Evaluate JavaScript expressions interactively. |
| Variables | Define and inspect JavaScript variables. |
| Functions | Create and call functions. |
| Objects | Inspect objects and their properties. |
| `.help` | Display REPL help. |
| `.exit` | Exit the interactive REPL. |
| Tab completion | Complete supported identifiers and expressions. |

The available behavior depends on the Node.js version and how the REPL is launched.

**Important:** starting Node.js in a Debian terminal gives you the native REPL, but it does not turn Debian into NodeOS. A NodeOS-style boot environment requires the appropriate kernel, root filesystem, startup configuration, and PID 1 arrangement.

---

## 📦 Commands and Packages

NodeOS uses a package-oriented approach to system utilities.

Its historical ecosystem includes utilities for file operations, networking, process inspection, and other system tasks.

Examples of familiar utility names include:

- `ls` — list directory contents.
- `cat` — display text files.
- `mkdir` — create directories.
- `cp` — copy files.
- `mv` — move or rename files.
- `rm` — remove files.
- `pwd` — display the current directory.
- `node` — invoke the Node.js runtime.
- `npm` — manage Node.js packages.

These are examples of utility names, not a guarantee that every command is installed in every NodeOS image.

In a REPL-first environment, the user can also work directly with JavaScript APIs instead of relying exclusively on shell commands.

For example:

```javascript
const fs = require("node:fs");

console.log(fs.readdirSync("."));
```

This uses Node.js filesystem APIs to list entries in the current working directory.

The exact APIs available in a NodeOS build depend on its Node.js version, security model, filesystem layout, and supported runtime features.

---

## 🐚 What About NSH?

NSH is associated with the NodeOS ecosystem and provides a shell-oriented interface.

A shell can make it easier to work with command names, arguments, external programs, and familiar terminal workflows. It can also provide functionality that is not part of the native Node.js REPL.

However, NSH and the Node.js REPL are different interfaces:

| Native Node.js REPL | NSH |
|---|---|
| Evaluates JavaScript directly. | Provides a shell-oriented command interface. |
| Uses native REPL commands such as `.help`. | Uses the commands and features supported by NSH. |
| Is part of the Node.js runtime. | Is a separate shell component. |
| Fits a direct JavaScript-first workflow. | Fits a command-oriented workflow. |

NSH is not inherently incompatible with NodeOS philosophy. The distinction is that a REPL-first system does not have to make NSH its primary interface.

For a system intended to expose Node.js immediately after boot, launching the native REPL directly is a natural design choice.

---

## 🛠️ Development

NodeOS is a historical project, so development should begin by inspecting the upstream source and its actual build instructions.

### Obtain the source

```bash
git clone https://github.com/NodeOS/NodeOS.git
cd NodeOS
```

### Inspect the project

```bash
cat README.md
cat package.json
```

Check the declared dependencies, scripts, required tools, and supported runtime versions before attempting a build.

### Check the installed runtime

```bash
node --version
npm --version
```

### Build and run

Follow the commands documented by the specific upstream revision you are using.

Do not assume that an old NodeOS revision will install or build successfully with a modern Node.js release. Its historical dependencies may require compatibility adjustments, and a successful npm installation alone does not prove that the operating system can boot.

---

## ⚠️ Compatibility

NodeOS originated in an older Node.js ecosystem. That matters when working with it today.

Potential compatibility issues include:

- 📦 Deprecated or unavailable npm dependencies.
- 🟢 Changes in Node.js APIs and runtime behavior.
- 🔧 Build scripts that rely on older toolchains.
- 🖥️ Differences between the original boot environment and a modern Linux distribution.
- 🔒 Permissions and system interfaces required for PID 1 operation.
- 📟 REPL startup behavior and process signal handling.

A modern Node.js REPL can be used as an interface prototype without requiring the entire historical NodeOS stack. A genuine NodeOS boot environment, however, needs a compatible and functional system image.

This README describes the project's philosophy and intended model. It does not claim that the original project currently builds cleanly on every platform or that a modern Node.js version is supported by every historical release.

---

## 🔗 Resources

- 🐙 **[NodeOS on GitHub](https://github.com/NodeOS/NodeOS)** — upstream operating-system repository.
- 📚 **[NodeOS command documentation](https://github.com/NodeOS/NodeOS/blob/master/docs/en/nsh/Commands.md)** — historical NSH command reference.
- 🟢 **[Node.js documentation](https://nodejs.org/docs/latest/api/)** — official Node.js API documentation.
- 📟 **[Node.js REPL documentation](https://nodejs.org/docs/latest/api/repl.html)** — native interactive console documentation.
- 📦 **[npm documentation](https://docs.npmjs.com/)** — package-management documentation.

---

## 💚 Final Thoughts

NodeOS explores a compelling idea: making JavaScript and Node.js foundational parts of an operating system instead of treating them only as applications running on top of one.

Its defining concept is not a particular prompt or command list. It is the relationship between the Linux kernel, Node.js userspace, and JavaScript-based system functionality.

For a REPL-first NodeOS environment, the ideal experience is simple:

```text
Welcome to Node.js
>
```

No custom shell is required just to make JavaScript the primary interface.

**NodeOS: a JavaScript-first approach to operating-system design.** 🚀

