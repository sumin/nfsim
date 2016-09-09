<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<html>
<head>
	<title>NFsim - download</title>

	<META NAME="description" CONTENT=".">
	<META NAME="keywords" CONTENT="">
	<link rel="stylesheet" type="text/css" href="../css/nf_style.css" />

</head>



<body>

	<center>
	<table border=0 cellspacing=0 cellpadding=0>
		<tr>
		<!-- <td width=30%></td> -->
		<td><img src="../images/topLogo.jpg" align=right></td>
		<td bgcolor=#2E3192 valign="center">
			<center>
			<div class="topMenuDiv">
				<a href="../" class="topMenu">overview</a>&nbsp&nbsp&nbsp
				<a href="../download" class="topMenu">download</a>&nbsp&nbsp&nbsp
				<a href="../pages/features.html" class="topMenu">features</a> &nbsp&nbsp&nbsp
				<a href="../pages/feedback.php" class="topMenu">feedback</a> <br>
				<a href="../pages/support/support.html" class="topMenu">support</a> &nbsp&nbsp&nbsp
				<a href="../pages/models/models.html" class="topMenu">models</a> &nbsp&nbsp&nbsp
				<a href="../pages/developers.html" class="topMenu">developers</a> &nbsp&nbsp&nbsp
				<a href="http://emonet.biology.yale.edu" class="topMenu">emonet lab</a>
			</div>
			</center>
		</td>
		<td bgcolor=#2E3192 width=15%></td>
		<td><img src="../images/topRight.jpg" align=left></td>
		<!-- <td bgcolor=#2E3192 width=50%></td> -->
	</tr>
	
	<tr>
		<td colspan=4>
		<br>
		<div class="sectionTitleDiv">download NFsim</div>
		</td>
	</tr>
	
	
	<tr>
		<td colspan=4>
		<center>
		<!--  CONTENT -->
		<!-- br><br>
		<b>Automatic registration and download is temporarily unavailble,<br> 
		but should be back in the next couple days.  Please contact <br> 
		michael.sneddon@yale.edu for access to the code.</b>
		<br><br -->
		

                
		<center>(not registered? click <a href="../download">here</a>.)</center>
		
		<table width=650> <tr><td>


<?php

	Header('Cache-Control: no-cache');
	Header('Pragma: no-cache');

	//first check if anything was posted
	$email = trim($_POST['email']);
	$password = trim($_POST['password']);
	
	//If it is empty, prompt for password
	if(empty($email)) {	
		
		echo("<form name=\"registerForm\" method=\"post\" action=\"\">\n");
		echo("<br><br><center><table border=0 cellspacing=1 cellpadding=4>\n");
		echo("<tr><td>");
		echo("<div class=\"regTextDiv\">Registered email</div></td>\n");
		echo("<td><input type=\"text\" name=\"email\" size=\"50\" rows=\"1\"></textarea> </td></tr>\n");
		echo("<tr><td>");
		echo("<div class=\"regTextDiv\">Password</div></td>\n");
		echo("<td><input type=\"password\" name=\"password\" size=\"50\" rows=\"1\"></textarea> </td></tr>\n");
		echo("</table></center>\n");
		echo("<br><center><input type=\"submit\" name=\"submit\" value=\"Login\" /> </center>\n");
		
	} else  {
		
		// check password in the database		
		require_once('verify.php');
		$valid="";
		verifyEmail ($email, $password, $valid);
		
		//NOT VALID!!!
		if($valid!=1) {
			echo("<center><br><br><font color=#FF0000>The email / password was not recognized!  Please try again.</font></center>\n");
			echo("<form name=\"registerForm\" method=\"post\" action=\"\">\n");
			echo("<br><br><center><table border=0 cellspacing=1 cellpadding=4>\n");
			echo("<tr><td>");
			echo("<div class=\"regTextDiv\">Registered email</div></td>\n");
			echo("<td><input type=\"text\" name=\"email\" size=\"50\" rows=\"1\"></textarea> </td></tr>\n");
			echo("<tr><td>");
			echo("<div class=\"regTextDiv\">Password</div></td>\n");
			echo("<td><input type=\"password\" name=\"password\" size=\"50\" rows=\"1\"></textarea> </td></tr>\n");
			echo("</table></center>\n");
			echo("<br><center><input type=\"submit\" name=\"submit\" value=\"Login\" /> </center>\n");
		} else if($valid==1) {
			
			
		?>
		
					
			<br><br><br>
			
			<center>
			<table border=0 width=640 border=0 cellspacing=0 cellpadding=0>
			    <tr>
				    <td>
					    <table border=0 width=640 border=0 cellspacing=0 cellpadding=0> <tr><td>
					    <td><img src="../images/topLeft.jpg" height=44 align=right></td>
						<td bgcolor=#2E3192>
							<div class="downloadTitleDiv">
								<center>Full Distribution, Stable Release (includes source)</center>
							</div>
						</td>
						<td><img src="../images/topRight.jpg" height=44 align=left></td>
						</td></tr></table>
					</td>
				</tr>
				<tr>
					<td width=640 border=0>
						<center>
						<br>This is the recommended download.  It includes all binaries, source files, 
						example models, and the user manual.  The full distribution is packaged with
						<a href="http://bionetgen.org">BioNetGen</a> and so it includes everything you need to get started with modeling,
						simulation, and even code development.
						<br><br>
						Note that <a href="http://rulebender.org">rulebender</a> is now available if you want a user interface for designing NFsim or BioNetGen models!
						</center>
						<br><br>
					</td>
				</tr>
				<tr>
					<td>
						<center>
						<table border=0 border=0 cellspacing=0 cellpadding=0> 
						<tr><td width=300>
								<div class="downloadTableText">
								Zip file (19.1 MB, Oct 2012)
								</div>
							</td>
							<td>
								<!-- div class="downloadTableText" -->
								<!--
								<form name="registerForm" method="post" action="d.php?f=NFsim_v1.08.zip">
									<?php echo("<input type=\"hidden\" name=\"e\" value=\"$email\" />") ?>
									<?php echo("<input type=\"hidden\" name=\"p\" value=\"$password\" />") ?> 
									<input type="submit" name="submit" value="NFsim_v1.08.zip" />
								</form>
								-->
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.11.zip">
									<input type="submit" name="submit" value="NFsim_v1.11.zip" />
								</form>
								</div>
						
									</td>
						</tr>
							
						<tr>
								<td width=300>
									<div class="downloadTableText">
									Compressed tarball (18.6 MB, Oct 2012)
									</div>
								</td>
								<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.11.tar.gz">
									<input type="submit" name="submit" value="NFsim_v1.11.tar.gz" />
								</form>
								
								
						</td></tr>
						
						
						
							
						
						
						</table>		
						</center>
				
					</td>
				</tr>

			</table>
			
			
			
			
			<br><br><br>
			
			<table border=0 width=640>
			
			
				<tr><td>
					    <table border=0 width=640 border=0 cellspacing=0 cellpadding=0> <tr><td>
					    <td><img src="../images/topLeft.jpg" height=44 align=right></td>
						<td bgcolor=#2E3192>
							<div class="downloadTitleDiv">
								<center>Tutorials and Documentation</center>
							</div>
						</td>
						<td><img src="../images/topRight.jpg" height=44 align=left></td>
						</td></tr></table>
					</td>
				</tr>
				<tr>
					<td>
						<!-- This is the recommended download.  It includes all binaries, source files, 
						example models, and the user manual.  The full distribution is packaged with
						<a href="http://bionetgen.org">BioNetGen</a> and so it includes everything you need to get started with modeling,
						simulation, and even code development. -->
						<br><br>
					</td>
				</tr>
				<tr>
				
					<td>
					<center>
						<table border=0 border=0 cellspacing=0 cellpadding=0> 
						<tr><td width=300>
							<div class="downloadTableText">
								User manual only
							</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="d.php?f=NFsim_manual_v1.11.pdf">
									<?php echo("<input type=\"hidden\" name=\"e\" value=\"$email\" />") ?>
									<?php echo("<input type=\"hidden\" name=\"p\" value=\"$password\" />") ?> 
									<input type="submit" name="submit" value="NFsim_manual_v1.11.pdf" />
								</form>
							</td>
						</td></tr>
						
						
						
						</table>
					</center>
					</td>
				</tr>
			</table>
			
			<br><br><br><br>
			
			
			<table border=0 width=640 border=0 cellspacing=0 cellpadding=0>
			    <tr>
				    <td>
					    <table border=0 width=640 border=0 cellspacing=0 cellpadding=0> <tr><td>
					    <td><img src="../images/topLeft.jpg" height=44 align=right></td>
						<td bgcolor=#2E3192>
							<div class="downloadTitleDiv">
								<center>Old Distributions</center>
							</div>
						</td>
						<td><img src="../images/topRight.jpg" height=44 align=left></td>
						</td></tr></table>
					</td>
				</tr>
				<tr>
					<td width=640 border=0>
						<center><br>
						This is an archive of old distributions.  If you are new to <br>
						NFsim, you should download the current version above instead.
						</center>
						<br><br>
					</td>
				</tr>
				
				<tr><td>
				<center>
						<table border=0 cellspacing=0 cellpadding=0> 
						
						
						
						<tr><td width=300>
								<div class="downloadTableText">
								August 2011, v1.10
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.10.zip">
									<input type="submit" name="submit" value="NFsim_v1.10.zip" />
								</form>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.10.tar.gz">
										<input type="submit" name="submit" value="NFsim_v1.10.tar.gz" />
								</form>
								</div>
						
							</td>
						</tr>
						<tr><td width=300 colspan=2>
								<br><br>
						</td></tr>
						
						
						
						
						<tr><td width=300>
								<div class="downloadTableText">
								April 2011, v1.09
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.09.zip">
									<input type="submit" name="submit" value="NFsim_v1.09.zip" />
								</form>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.09.tar.gz">
										<input type="submit" name="submit" value="NFsim_v1.09.tar.gz" />
								</form>
								</div>
						
							</td>
						</tr>
						<tr><td width=300 colspan=2>
								<br><br>
						</td></tr>
						
						
						
						
						<tr><td width=300>
								<div class="downloadTableText">
								December 2010, v1.08
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.08.zip">
									<input type="submit" name="submit" value="NFsim_v1.08.zip" />
								</form>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.08.tar.gz">
										<input type="submit" name="submit" value="NFsim_v1.08.tar.gz" />
								</form>
								</div>
						
							</td>
						</tr>
						
						
						
						<tr><td width=300 colspan=2>
								<br><br>
						</td></tr>
						
						<tr><td width=300>
								<div class="downloadTableText">
								September 2010, v1.06
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.06.zip">
									<input type="submit" name="submit" value="NFsim_v1.06.zip" />
								</form>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.06.tar.gz">
										<input type="submit" name="submit" value="NFsim_v1.06.tar.gz" />
								</form>
								</div>
						
							</td>
						</tr>
						
						<tr><td width=300 colspan=2>
								<br><br>
						</td></tr>
						<tr><td width=300>
								<div class="downloadTableText">
								May 2010, v1.052
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.052.zip">
									<input type="submit" name="submit" value="NFsim_v1.052.zip" />
								</form>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFsim_v1.052.tar.gz">
										<input type="submit" name="submit" value="NFsim_v1.052.tar.gz" />
								</form>
								</div>
						
							</td>
						</tr>
						</table>
				</td></tr>
				

			</table>
			
			
			<br><br><br>
			
			<center>
			<table border=0 width=640 border=0 cellspacing=0 cellpadding=0>
				<tr>
				    <td>
					    <table border=0 width=640 border=0 cellspacing=0 cellpadding=0> <tr><td>
					    <td><img src="../images/topLeft.jpg" height=44 align=right></td>
						<td bgcolor=#2E3192>
							<div class="downloadTitleDiv">
								<center>NFpop, Beta Release (includes source)</center>
							</div>
						</td>
						<td><img src="../images/topRight.jpg" height=44 align=left></td>
						</td></tr></table>
					</td>
				</tr>
				<tr>
					<td width=640 border=0>
						<center>
						<br>This is the original beta release of NFpop (based on NFsim build 1.09b), written by Justin Hogg
						to enable hybrid particle-population simulation.  For more information, see the documentation
						on this project <a href="http://bionetgen.org/index.php/Hybrid_particle-population_model_generator"> here </a>.
						Note that the features of NFpop are now part of the standard, stable NFsim package starting at
						NFsim_v1.11.
						<br><br>
					</td>
				</tr>
				<tr>
					<td>
						<center>
						<table border=0 border=0 cellspacing=0 cellpadding=0> 
						<tr><td width=300>
								<div class="downloadTableText">
								Zip file (9.35 MB, Aug 2011)
								</div>
							</td>
							<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFpop_v1.09p.zip">
									<input type="submit" name="submit" value="NFpop_v1.09p.zip" />
								</form>
								</div>
						
									</td>
						</tr>
							
						<tr>
								<td width=300>
									<div class="downloadTableText">
									Compressed tarball (9.18 MB, Aug 2011)
									</div>
								</td>
								<td>
								<form name="registerForm" method="post" action="z1859237a561037f13957t10nkl57192759s1/NFpop_v1.09p.tar.gz">
									<input type="submit" name="submit" value="NFpop_v1.09p.tar.gz" />
								</form>
								
								
						</td></tr>
						
						
						
							
						
						
						</table>		
						</center>
				
					</td>
				</tr>

			</table>
			
			
			
			
			
			<br><br><br><br><br><br>
		
		<?php

		} else {
			echo("<center>something went wrong, very wrong.</center>\n");
		}
	}
	
?>

	

	





</td></tr></table>
<!-- END CONTENT -->
		
	</td>
	</tr>
</table>
</center>

</body>
</html>
