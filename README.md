
# Node64

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Courier+New&size=32&duration=2500&pause=800&color=00FF99&center=true&vCenter=true&width=650&lines=Node64;Linux+%2B+Node.js;A+little+OS+experiment" alt="Node64 animated title" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/status-experimental-orange?style=flat-square" />
  <img src="https://img.shields.io/badge/kernel-Linux-blue?style=flat-square" />
  <img src="https://img.shields.io/badge/runtime-Node.js-green?style=flat-square" />
  <img src="https://img.shields.io/badge/architecture-ARM64-lightgrey?style=flat-square" />
  <img src="https://img.shields.io/badge/license-MIT-yellow?style=flat-square" />
</p>

<p align="center">
  <i>What if JavaScript was one of the first things you saw when booting an OS?</i>
</p>

---

## `> hello, node64`

Node64 is a small operating system experiment built around Linux and Node.js.

The idea is simple: take a Linux boot environment, put Node.js at the center of the experience, and see where it goes.

It's not trying to replace your desktop Linux installation. It's a project for experimenting with booting, root filesystems, JavaScript, and the bits that glue everything together.

Still a work in progress. Things may break. That's part of the fun.

```text
         _   __          __     
         / | / /___  ____/ /__  
        /  |/ / __ \/ __  / _ \
       / /|  / /_/ / /_/ /  __/ 
      /_/ |_/\____/\__,_/\___/

         Linux meets JavaScript
```

## The idea

```text
Power on
   |
   v
Linux kernel
   |
   v
Initial filesystem
   |
   v
Node.js
   |
   v
JavaScript
```

That's the general idea behind Node64. The exact boot sequence depends on the current scripts and filesystem setup.

## What's in here?

```text
Node64/
├── appsrc/
├── boot/
├── initramfs/          # local files, ignored by Git
├── src/
├── userfs/
├── LICENSE.md
├── README.md
└── package.json
```

- `appsrc/` — application source files.
- `boot/` — boot-related files and artifacts.
- `initramfs/` — local working filesystem. Not tracked by Git.
- `src/` — utilities and packaging scripts.
- `userfs/` — root filesystem archive and related data.
- `package.json` — project metadata and commands.

The layout will probably change as the project develops.

## A few things

- 🐧 Linux kernel underneath.
- 🟢 Node.js and JavaScript at the center of the experiment.
- 📦 A separate root filesystem workflow.
- 🛠️ Scripts for packing, unpacking, and running configured environments.
- 🧪 Experimental, because this is where the interesting stuff happens.
- 📀 Node.js is init and userspace 

## Getting the code

```bash
git clone https://github.com/Francesco12o/Node64.git
cd Node64
```

Or, if you use SSH:

```bash
git clone git@github.com:Francesco12o/Node64.git
cd Node64
```

You'll need a suitable Linux environment and the tools required by the particular workflow you want to run.

## Commands

The available npm scripts are defined in `package.json`.

| Command | What it is for |
|---|---|
| `npm run boot` | Configured boot workflow |
| `npm run vncserver` | VNC-related workflow |
| `npm run spice` | SPICE-related workflow |
| `npm run unpack` | Unpack the filesystem archive |
| `npm run chroot` | Configured chroot workflow |
| `npm run pack` | Package the filesystem |

The scripts may depend on local files, permissions, and system tools. Check their definitions before running them.

## The filesystem thing

The working `initramfs/` directory is ignored on purpose.

It's where local filesystem contents can live without dumping every generated file into Git. The tracked `userfs/` directory contains the archive used by the project workflow.

In other words:

```text
Tracked files
     |
     +---- source code
     +---- scripts
     +---- package metadata
     +---- root filesystem archive
                  |
                  v
             unpack / edit
                  |
                  v
              initramfs/
                  |
                  v
                pack
```

If you're changing the filesystem, keep a backup of the archive before replacing it.

## Animated terminal corner

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Courier+New&size=18&pause=1000&color=00FF99&center=true&vCenter=true&width=700&lines=%24+uname+-s;Linux;%24+node;Welcome+to+Node64;%24+console.log('hello+world');hello+world" alt="Animated terminal commands" />
</p>

```javascript
console.log("hello from Node64");
```

Nothing fancy. Just JavaScript, and the possibility of doing more with it.

## Screenshots

No polished screenshots yet. I'd rather put real output here once the boot workflow is ready to show.

<!-- Add a screenshot here when you have one.
<p align="center">
  <img src="docs/images/node64.png" width="720" alt="Node64 running" />
</p>
-->

## Current state

Node64 is experimental. The kernel, filesystem, scripts, and runtime setup are still being worked on.

Don't assume every script works on every Linux distribution or architecture. The environment used during development may be different from yours.

If you try it and something fails, the actual error output is more useful than a screenshot of the error.

## Notes

- Don't commit secrets or private keys.
- Don't commit the local `initramfs/` directory.
- Keep copies of important filesystem archives.
- Check scripts before running them as root.
- Booting an OS is a little different from running a regular Node.js application.

## License

MIT. See [LICENSE.md](LICENSE.md).

---

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Courier+New&size=16&pause=1200&color=888888&center=true&vCenter=true&width=500&lines=Built+one+piece+at+a+time.;Still+experimenting.;Thanks+for+checking+out+Node64." alt="Animated footer" />
</p>

<p align="center">
  <sub>Node64 — Linux, JavaScript, and a bunch of experiments.</sub>
</p>
