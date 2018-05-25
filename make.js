/**
 * Makefile generator
 * 
 * Generate a makefile and dependencies link by reading headers
 * 
 * @author Alexandre Penombre <aluzed_AT_gmail.com>
 * @copyright 2018 ©
 */
const path = require('path');
const fs = require('fs');
const Handlebars = require('handlebars');
const DeepScan = require('deep-scan');
const beautify = require("json-beautify");
const config = require('./builder/config.json');

const util = require('util');
const exec = util.promisify(require('child_process').exec);

// Paths
const makefilePath = path.join(__dirname, 'Makefile');
const dependenciesPath = path.join(__dirname, './builder/dependencies.json');
const buildPath = path.join(__dirname, 'build');
const includePath = path.join(__dirname, 'include');
const srcPath = path.join(__dirname, 'src');

// Relative paths
const relativeBuildPath = "./" + buildPath.substring(__dirname.length + 1, buildPath.length) + "/";
const relativeSrcPath = "./" + srcPath.substring(__dirname.length + 1, srcPath.length) + "/";
const relativeIncludePath = "./" + includePath.substring(__dirname.length + 1, includePath.length);

// Handlebars templates
const skelTplPath = path.join(__dirname, './builder/skeleton.hbs');
const objectTplPath = path.join(__dirname, './builder/object.hbs');
const skelContent = fs.readFileSync(skelTplPath, 'utf8');
Handlebars.registerPartial('objTpl', fs.readFileSync(objectTplPath, 'utf8'));
const skelTpl = Handlebars.compile(skelContent);

function readHeaderDependencies() {
  console.log('Checking dependencies...');

  let dependencies = {};

  function cleanDependencies() {
    if(fs.existsSync(dependenciesPath)) {
      fs.unlinkSync(dependenciesPath);
    }
  }

  function getIncludes(path) {
    let content = fs.readFileSync(path, 'utf8');
    return content.split("\n")
      .filter(l => l !== "")
      .filter(l => l.match(/^#include\s/))
      .filter(l => !l.match(/\//))
      .filter(l => !l.match(/<.+>/));
  }

  cleanDependencies();

  DeepScan(includePath, file => {
    let includes = getIncludes(file);

    if(includes.length > 0) {
      dependencies[path.basename(file).replace(/\.h$/, '')] = includes.map(i => i
          .replace('#include ', '')
          .replace(/"/g, '')
          .replace(/\.h$/, '.o')
          .trim());
    }
  }, [/.+\.h$/], 'ONLY', 0);

  fs.writeFileSync(dependenciesPath, beautify(dependencies, null, 2, 80), { flag: 'w+' });
}

function renderMakeFile() {
  console.log('Generating Makefile...');

  const dependencies = require("./builder/dependencies.json");
  let data = {
    main: config.main,
    classNames: [],
    relativeBuildPath,
    relativeIncludePath,
    relativeSrcPath
  };

  for(let cl in config.classNames) {
    data.classNames.push({
      name: config.classNames[cl],
      dependencies: dependencies[config.classNames[cl]] || [],
      relativeBuildPath,
      relativeIncludePath,
      relativeSrcPath
    })
  }

  let makeStr = skelTpl(data);

  fs.writeFileSync(makefilePath, makeStr);
  console.log('Make file generated');
}

readHeaderDependencies();

renderMakeFile();

async function make() {
  console.log('Building...');

  const { stdout, stderr } = await exec('make');
  console.log(stdout);

  if(stderr.trim() !== "") {
    console.error(stderr);
  }
}

make();