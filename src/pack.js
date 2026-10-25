
'use strict';

const path = require('node:path');
const { spawnSync } = require('node:child_process');
const fs = require('node:fs');

const rootfs = path.resolve(__dirname, '../userfs/initramfs');
const output = path.resolve(__dirname, '../boot/initramfs.img');

if (!fs.existsSync(rootfs) || !fs.statSync(rootfs).isDirectory()) {
    console.error('Error: userfs/initramfs/ does not exist.');
    console.error('Extract the initramfs yourself before packing.');
    process.exit(1);
}

fs.mkdirSync(path.dirname(output), { recursive: true });

console.log(`Packing rootfs: ${rootfs}`);
console.log(`Output image:   ${output}`);

const find = spawnSync(
    'sh',
    ['-c', 'find . -print0 | cpio --null -o --format=newc | gzip -9'],
    {
        cwd: rootfs,
        encoding: 'buffer',
        stdio: ['ignore', fs.openSync(output, 'w'), 'inherit']
    }
);

if (find.error || find.status !== 0) {
    console.error('Error: initramfs packing failed.');
    try { fs.unlinkSync(output); } catch {}
    process.exit(1);
}

console.log('Node64 initramfs.img packed successfully!');
