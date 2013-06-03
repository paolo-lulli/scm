<?php

$project_name=$_REQUEST['n'];
$scm_policy="public";// or private
//##################################


$scm_model="git";
$operation="init";



function initialize($project_name){
$git_repos_home="/home2/dbthunde/src.repos";
$git_repos_http="/home2/dbthunde/www/src.lulli.net/projects";
	$output=array();
	$repo_name = $git_repos_home."/".$project_name. ".git";
	print "repo_name=[$repo_name]";
	if (! file_exists($repo_name) ){
		mkdir($repo_name, 0700);
		$output[]=exec("cd $repo_name && git --bare init");
		if ($scm_policy="public"){
			$output[]=exec("cd $repo_name/hooks && cp post-update.sample post-update");
			$output[]=exec("chmod +x  $repo_name/hooks/post-update");
			$output[]=exec("cd $repo_name/hooks && git update-server-info");
			//ln -s $(pwd)/ReactReader.git $HOME/www/open/ReactReader.git
			$output[]=exec("ln -s $repo_name $git_repos_http");
		}
		foreach($output as $oo){
			print "$oo";
		}
	} else {
		print "File [$repo_name] already exists, SKIPPING...\n";
	}

}


if ( "" != $project_name){
	initialize($project_name);
} else {
	print "MISSING PROJECT NAME";
}
?>
