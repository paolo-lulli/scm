<?php


require_once("settings.inc");
class Fossil 
{

var $repo;
var $comment;
var $artifacts = array();
var $commented=false;
var $repo_file;
var $stage;
var $cgi;
var $user;
var $password;

public function __construct($repo){
	$this->repo=$repo;
	$this->repo_file = REPOS_HOME 	.  "$this->repo" . ".fossil";
	$this->stage 	= STAGING_AREA 	. "//" . "$this->repo";
	$this->cgi 	= CGI_HOME 	. "//" . "$this->repo";
	$this->cgi_script 	= $this->cgi . "//" . "$this->repo" . ".cgi";
}

public function init()
{
	if (!is_file( $this->repo_file )){
		$output = shell_exec(FOSSIL_EXECUTABLE." new ". $this->repo_file );
	} else {
		$output = "Repository Already exists\n";
	}
	print "$output";
	$this->createCgi();
}

public function newA()
{
	$this->init();
}

//TODO
public function open(){
	if(! is_dir($this->stage)){
		//mkdir($this->stage, 0, true);
		mkdir($this->stage, 0700, true);
	}
	if (chdir($this->stage)){
		$output =shell_exec(FOSSIL_EXECUTABLE." open ". $this->repo_file);
	} else {
		$output = "Cannot chdir() to $this->stage";
	}
	print $output;
}

//N.B.: NO RECURSION
public function add($artifact){
	if(! is_dir($this->stage)){
		//mkdir($this->stage, 0, true);
		mkdir($this->stage, 0700, true);
	}
	if (chdir($this->stage)){
		array_push($this->artifacts, $artifact);
		foreach( $this->artifacts as $item ) {
			$output =shell_exec(FOSSIL_EXECUTABLE." add ". $item);
	}
	} else {
		$output = "Cannot chdir() to $this->stage";
		print $output;
	}
}

public function update(){
	if (chdir($this->stage)){
		$output =shell_exec(FOSSIL_EXECUTABLE." update ");
	} else {
		$output = "Cannot chdir() to $this->stage";
		print $output;
	}

}
public function comment($comment){
	$this->comment = $comment;
	$this->commented=true;
}

public function commit(){
	if($this->commented){
		if (chdir($this->stage)){
			$output =shell_exec(FOSSIL_EXECUTABLE." commit ");
			print $output;
			print "commit()\n";
		} else {
			print "Cannot chdir() to $this->stage";
		}
	} else {
		print "Should ->comment() before commit()\n";
	}
}

private function createCgi(){

$cgiScript = <<<EOF
#! /usr/bin/env fossil
repository: $this->repo_file
EOF;

	if(! is_dir($this->cgi)){
		//mkdir($this->cgi, 0, true);
		mkdir($this->cgi, 0700, true);
	}
	if (chdir($this->cgi)){
		if(!is_file($this->cgi_script)){
			file_put_contents($this->cgi_script, $cgiScript);	
		}	
	} else {
		print "Cannot chdir() to $this->cgi";
	}

}
///////////////////////////77

public function setPassword($password){
	$this->password=$password;
	$output =shell_exec(FOSSIL_EXECUTABLE." user password " .$this->user ." " .$this->password);
}
public function setUser($user){
	$this->user=$user;
}

}
?>
